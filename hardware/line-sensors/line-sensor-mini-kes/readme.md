# Line Follower board for use with the Cytron Maker Nano RP2040


This board is specifically designed for half width line following using the latest V1.3 UKMARSBOT main board where the CPU board only has four A to D sensor input, such as the Cytron Maker Nano RP2040. 

It is a simplified version of the standard mini wide half line sensor board which uses 6 sensor inputs. The board has the additional text on it that says “1/2 line for Pico”. 

The Cytron Maker Nano RP2040 is a 3.3V device, so if you are using it instead of the standard Arduino Nano there are a couple of points to note. 

1. The 5V output from the CPU board has to be disabled, either by cutting off the 5V output pin or by not having a connector at that pin for the 5V output to go into, and 
2. The 3.3V pin and the 5v pin on the sensor board J1 connector should be connected, which means that everything on the board now runs at 3.3Volts. 
 
This board just has 3 LEDs and 4 transistors and uses only 1 transistor to drive the LEDs. Because it runs at 3.3V the LED resistors have been reduced from 68 to 33 ohms. The side sensors now feed in to A0 and A3 and the 2 central line sensors feed in to A1 and A2. The full set of build instructions for populating the board can be found at https://www.davidhannaford.com/kes2025/kes2025linesensor.pdf

There is also a copy in this directory.

You can find the KiCad project in the ecad dirctory under [ecad/line-sensor-mini-kes](../line-sensor-mini-kes/)