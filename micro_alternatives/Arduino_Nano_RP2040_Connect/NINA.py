# Arduino Nano RP2040 Connect WifiNINA support
#
# Copyright (c) 2023 Rob Probin
#
# MIT License
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import machine
import time
from machine import Pin


# Cmd Struct Message
#  _________________________________________________________________________________
# | START CMD | C/R  | CMD  |[TOT LEN]| N.PARAM | PARAM LEN | PARAM  | .. | END CMD |
# |___________|______|______|_________|_________|___________|________|____|_________|
# |   8 bit   | 1bit | 7bit |  8bit   |  8bit   |   8bit    | nbytes | .. |   8bit  |
# |___________|______|______|_________|_________|___________|________|____|_________|

START_CMD = 0xE0 
END_CMD = 0xEE 
ERR_CMD = 0xEF 
REPLY_FLAG = 1 << 7

class NINA_SPI:
    def SPI_NINA_deselect(self):
        NINA_CS.high()

    def wait_slave_ready(self):
        return NINA_READY.value()==0
    
    def SPI_wait_for_NINA_ready(self):
        # the C++ code waits forever or watchdogs the processor. We do it for 1 second
        start = time.ticks_ms()
        while not self.wait_slave_ready():
            if (time.ticks_ms() - start) > 1000:
                # abort
                print("NINA not ready in 1 second")
                return

    def SPI_NINA_select(self):
        NINA_CS.low()
    
        # wait for up to 5 ms for the NINA to indicate it is not ready for transfer
        # the timeout is only needed for the case when the shield or module is not present
        start = time.ticks_ms()
        while NINA_READY.value() != 1 and (time.ticks_ms() - start) < 5:
            pass
        
    def SPI_wait_for_SS(self):
        self.SPI_wait_for_NINA_ready()
        self.SPI_NINA_select()

    def __init__(self):
        global NINA_CS
        global NINA_READY
        global NINA_RESET
        global NINA_GPIO0
        global NINA_IRQ
        
        NINA_CS = Pin(9, Pin.OUT)
        NINA_READY = Pin(10, Pin.IN)
        NINA_RESET = Pin(3, Pin.OUT)
        NINA_GPIO0 = Pin(2, Pin.OUT) # same as NINA_IRQ
        NINA_IRQ = NINA_GPIO0 # same as NINA_GPIO0

        NINA_GPIO0.high()
        NINA_CS.high()
        NINA_RESET.low()
        time.sleep_ms(10)
        NINA_RESET.high()
        time.sleep_ms(750)
        
        NINA_GPIO0.low()
        NINA_IRQ.init(NINA_IRQ.IN)

        self.spi = machine.SPI(1, baudrate=8000000, sck=machine.Pin(14), mosi=machine.Pin(11), miso=machine.Pin(8))

        
    def SPI_send_cmd(self, command, number_of_parameters):
        if number_of_parameters != 0:
            data = bytes([START_CMD, command, number_of_parameters])
        else:
            data = bytes([START_CMD, command, number_of_parameters, END_CMD])
        #print(data.hex())
        self.spi.write(data)

    def SPI_read_8(self):
        return self.spi.read(1)[0] #, write=0xFF)[0]
    
    def SPI_wait_SPI_char(self, waitChar):
        start = time.ticks_ms()
        while (time.ticks_ms() - start) < 1000:
            newChar = self.SPI_read_8()
            if newChar == waitChar:
                return True
            elif newChar == ERR_CMD:
                return False
        return False
        
    def SPI_get_response_command(self, command, expected_return_parameters):
        if not self.SPI_wait_SPI_char(START_CMD):
            print("Not start")
            return None

        if self.SPI_read_8() != (REPLY_FLAG+command):
            print("Wrong command")
            return None

        # check correct number of params
        if self.SPI_read_8() == expected_return_parameters:
            # weirdly the C++ only returns the first parameter

            #data = []
            #for i in range(expected_return_parameters):
            param_len = self.SPI_read_8()
            # now get the data
            data = self.spi.read(param_len) #, write=0xFF)
        else:
            print("wrong params")
            return None

        if self.SPI_read_8() != END_CMD: print("No end?")  # ignored @TODO check?
        return data
    
    def SPI_send_param8(self, data_byte, last_param=False):
        # send one byte!
        if last_param:
            data = bytes([1, data_byte, END_CMD])
        else:
            data = bytes([1, data_byte])
        #print(data.hex())
        self.spi.write(data)


SET_PIN_MODE = 0x50
SET_DIGITAL_WRITE = 0x51
SET_ANALOG_WRITE = 0x52
GET_DIGITAL_READ = 0x53
GET_ANALOG_READ = 0x54
GET_FW_VERSION_CMD = 0x37

PIN_INPUT = 0
PIN_OUTPUT = 1
PIN_INPUT_PULLUP = 2
PIN_INPUT_PULLDOWN = 3
PIN_OUTPUT_OPENDRAIN = 4

NinaPin_LEDR = 27
NinaPin_LEDG = 25
NinaPin_LEDB = 26
NinaPin_A4 = 34
NinaPin_A5 = 39
NinaPin_A6 = 36
NinaPin_A7 = 35
    
def toAnalogPin(pin):
  if   (pin == 4): return 6 # ADC1 - CH6
  elif (pin == 5): return 3 # ADC1 - CH3
  elif (pin == 6): return 0 # ADC1 - CH0
  elif (pin == 7): return 7 # ADC1 - CH7
  else:            return 0xFF


class NINA:
    def __init__(self):
        self.spi = NINA_SPI()
        
    def _send1(self, command, parameter):
        self.spi.SPI_wait_for_SS()
        self.spi.SPI_send_cmd(command, 1)
        self.spi.SPI_send_param8(parameter, last_param=True)

        # pad to multiple of 4
        self.spi.SPI_read_8()
        self.spi.SPI_read_8()

        self.spi.SPI_NINA_deselect()


    def _send2(self, command, parameter1, parameter2):
        self.spi.SPI_wait_for_SS()
        self.spi.SPI_send_cmd(command, 2)
        self.spi.SPI_send_param8(parameter1)
        self.spi.SPI_send_param8(parameter2, last_param=True)


        number_of_parameters = 2
        #data = bytes([START_CMD, command, number_of_parameters, 1, parameter1, 1, parameter2, END_CMD, 0xFF])
        #print(data.hex())
        #self.spi.spi.write(data)
            
        # pad to multiple of 4
        self.spi.SPI_read_8()
        time.sleep_ms(10)

        self.spi.SPI_NINA_deselect()


    def _rcv(self, command, expected_number_of_parameters):
        # Wait the reply 
        self.spi.SPI_wait_for_NINA_ready()
        self.spi.SPI_NINA_select()

        data = self.spi.SPI_get_response_command(command, 1)
        self.spi.SPI_NINA_deselect()
        return data
    
    def pinMode(self, pin, mode):
        self._send2(SET_PIN_MODE, pin, mode)
        data = self._rcv(SET_PIN_MODE, 1)

    def analogRead(self, pin):
        Apin = toAnalogPin(pin)
        self._send1(GET_ANALOG_READ, Apin)
        data = self._rcv(GET_ANALOG_READ, 1)
        if len(data) == 2:
            return (data[1]<<8)+data[0]
        else:
            print(" Unexpected return")
            return 0
        
    def getFwVersion(self):
        self.spi.SPI_wait_for_SS()
        self.spi.SPI_send_cmd(GET_FW_VERSION_CMD, 0)
        self.spi.SPI_NINA_deselect()
        
        self.spi.SPI_wait_for_NINA_ready()
        self.spi.SPI_NINA_select()
        data = self.spi.SPI_get_response_command(GET_FW_VERSION_CMD, 1)
        self.spi.SPI_NINA_deselect()
        return data

    def digitalWrite(self, pin, state):
        if state:	#invert state
            state = 0
        else:
            state = 1
        self._send2(SET_DIGITAL_WRITE, pin, state)
        data = self._rcv(SET_DIGITAL_WRITE, 1)
        #print()

    def analogWrite(self, pin, value0_255):
        self._send2(SET_ANALOG_WRITE, pin, value0_255)
        data = self._rcv(SET_ANALOG_WRITE, 1)
    
    def digitalRead(self, pin):
        # NOTE: I haven't tested this!
        self._send1(GET_DIGITAL_READ, pin)
        data = self._rcv(GET_DIGITAL_READ, 1)
        return data
        # Arduino C++ code has if (_data == 1) return HIGH; else return LOW;
        # but in Arduino.h it defines HIGH as 1 and LOW as 0, so I'm going leave this
        # for the moment. It might be there is an error return code, but I'm going
        # to ignore that for the moment until I test this.
        
def main():
    nina = NINA()
    #version = nina.getFwVersion()
    #print("Version", version)
    #nina.pinMode(NinaPin_A4, PIN_INPUT)
    #print("ADC reading", nina.analogRead(4))
    #nina.pinMode(NinaPin_A5, PIN_INPUT)
    #print("ADC reading", nina.analogRead(5))
    #nina.pinMode(NinaPin_A6, PIN_INPUT)
    #print("ADC reading", nina.analogRead(6))
    #nina.pinMode(NinaPin_A7, PIN_INPUT)
    #print("ADC reading", nina.analogRead(7))

    #nina.pinMode(NinaPin_LEDR, PIN_OUTPUT)
    nina.pinMode(NinaPin_LEDG, PIN_OUTPUT)
    #nina.pinMode(NinaPin_LEDB, PIN_OUTPUT)
    #nina.digitalWrite(NinaPin_LEDR, 0)
    #nina.digitalWrite(NinaPin_LEDG, 0)
    #nina.digitalWrite(NinaPin_LEDB, 0)
    
    while True:
        print("Red")
        nina.digitalWrite(NinaPin_LEDR, 1)
        time.sleep_ms(100)
        nina.digitalWrite(NinaPin_LEDR, 0)
        time.sleep_ms(100)
        print("Green")
        nina.digitalWrite(NinaPin_LEDG, 1)
        time.sleep_ms(100)
        nina.digitalWrite(NinaPin_LEDG, 0)
        time.sleep_ms(100)
        print("Blue")
        nina.digitalWrite(NinaPin_LEDB, 1)
        time.sleep_ms(100)
        nina.digitalWrite(NinaPin_LEDB, 0)
        time.sleep_ms(100)
    
    #time.sleep_ms(200)
    def glow(pin):        
        for level in range(255,-1, -1):
            nina.analogWrite(pin, level)
            time.sleep_ms(1)
        for level in range(256):
            nina.analogWrite(pin, level)
            time.sleep_ms(1)
            
    glow(NinaPin_LEDR)
    glow(NinaPin_LEDG)
    glow(NinaPin_LEDB)
    # they still glow afterwards https://forum.arduino.cc/t/rp2040-connect-rgb-led-still-glows-after-analogwrite-ledr-255/868632/7
    # looks like the Nina PWM is still on...
    
main()

