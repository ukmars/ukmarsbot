# Arduino Nano Robot Pinouts

Tha arduino nano has a good selection of IO pins in a 30 pin DIP footprint.

There are

 | Arduino Nano            | Specifications          |
 | :---------------------- | :---------------------- |
 | Microcontroller         | ATmega328P              |
 | Architecture            | AVR                     |
 | Operating Voltage       | 5 Volts                 |
 | Input                   | Voltage  (7-12) Volts   |
 | Flash                   | 30 KB + 2k booltolader  |
 | SRAM                    | 2KB                     |
 | EEPROM                  | 1 KB                    |
 | Clock                   | 16 MHz                  |
 | Analog                  | up to 8 Pins            |
 | DC                      | Max 40mA per pin        |
 | Digital                 | up to 22 pins           |
 | PWM                     | up to 6 channels        |
 | Power Consumption       | 19 mA                   |
 | PCB                     | Size  18 x 45 mm        |
 | Weight                  | 7g                      |


## Analogue Input
Up to 8 analogue input channels are available on pins A0 - A7. By default these have 10 bits of resolution (0..1023) and the analogue reference is 5 Volts. The reference voltage can be changed to 3.3V if necessary.

If not required for analogue inputs, pins A0..A5 are available as general purpose digital IO pins. When used as digital pins, A0..A5 may also be referred to as pin numbers 14..19 respectively.

Pins A4 and A5 have a special purpose use as I2C pins SDA and SCL respectively.

It is probaby best to assign purely analogue input functions to pins A7 and A6 first and then pins A0, A1, A2 and A3. That way, the I2C pins are allocated last and remain available for use al long as possible.

## Digital IO

There are a further 14 digital IO pins serving a variety of functions. These are labelled as pins 0..13. Due to the internal architecture of the AtMega328p and the design of the core Arduino software, some pins are expected to be used for certain purposes and it is best to use them for that where possible.

 | Pin   | Purpose                                                       |
 | :--: | ------------------------------------------------------------   |
 |   0  |  Serial RXD. Used by the bootloader and default serial port    |
 |   1  |  Serial TXD. used by the bootloader and default serial port    |
 |   2  |  INT0 - external interrupt - best for encoder interrupt        |
 |   3  |  INT0 - external interrupt - best for encoder interrupt        |
 |   4  |  usually free for any purpose                                  |
 |   5  |  OC0B - 960 Hz fast PWM - no interference from Tone or Servo   |
 |   6  |  OC0A - 960 Hz fast PWM - no interference from Tone or Servo   |
 |   7  |  usually free for any purpose                                  |
 |   8  |  usually free for any purpose                                  |
 |   9  |  OC1A  Timer 1 output compare A - Used by Servo library        |
 |  10  |  OC1B  Timer 1 output compare B - Used by Servo library        |
 |  11  |  MOSI  SPI data in - SPI needs this pin if you use it          |
 |  12  |  MISO  SPI data out - SPI needs this pin if you use it         |
 |  13  |  SCK and status LED - good for user feedback                   |


## Analogue Output (PWM)

While there are several pins that can deliver a PWM signal (3,5,6,9,10,11), there are some constraints.

The AtMega328p has three timers. All are set up by default with a prescaler of 64 and so will be running at 250kHz on the nano.

**Timer 0** is used to provide the timebase for the millis() function (actually 960us). It is probably not a good idea to alter this as so much code relies on millis() for correct functioning. Because Timer0 has two Output Compare Registers, the Arduino core sets up these channels for 8 bit fast PWM and the OC0A and OC0B outputs can be activated on pins 5 and 6. The frame rate will be that of the Timer 0 counter - 960kHz. This will probably work well enough with many motors but the frequency is effectively fixed because of the need to leave the Timer 0 interrupt frequency alone. No other libraries will normally alter Timer 0 for the same reason. Thus, these two PWM pins are pretty safe to use.

**Timer 1** is set up by default in 8 bit phase correct PWM mode which can be output on pins 9 and 10. This mode will have a frame frequency of about 490 Hz which may be a bit low. Timer 1 is used by the Servo library which will overwrite any user settings so the use of Servos should be considered incompatible with PWM generation on these pins. If they *are* used for PWM, there are options available to change the frequency and resolution of the output and these may be worth exploring if the default 8 bits resolution at 490 Hz is not suitable.

**Timer 2** is similar to Timer 1 and can be used to generate PWM on pins 3 and 11. The defaults are the same as those for Timer 1. However, there are two conflicts to be aware of. First it the use of the Tone library which will reconfigure Timer 2. More significant for a robot controller is that pin 3 on the Arduino is one of the two external interrupt pins which will be needed for encoders.

## External Interrupts

Almost all of the Arduino pins can be used to generate pin change interrupts. This does _not_ include the ability to distinguish between falling and rising edges. Only two pins can do that - pins 2 and 3. For an encoder input, the minimum requirement is to generate an interrupt on one of the edges of one of the channels - X1 operation. That will give the ability to count up and down by sampling the state of the other channel on the same encoder. For X2 operation, the processor will have to be able to detect both rising and falling edges and alternate between them. It is relatively simple to switch the edge type when servicing the interrupt. Again,the other channel must be sampled in the interrupt so that the direction can be deduced. Full X4 operation would mean looking at the rising and falling edges of both channels. Since that would require both the external interrupt pins, it is not feasible for inputs from two motors but could be done with a single encoder on one motor.

# Robot Pin Requirements

Most likely, the following would be needed for the functions in a small multi-purpose robot:

 | Function   | Requirement   | Candidate Arduino pins |
 | ---------- | ------------- | ---------- |
 | Motor Drive |  Four pins. Each motor needs PWM plus direction |  5 - PWM Left<br>6 - PWM Right<br>7 - Dir Left<br>8 - Dir Right  |
 | Encoders    |  Four pins. Chan A/B for each motor  |  2 - Left, Chan A<br>3 - Right, Chan A<br>9 - Left, Chan B<br>10 - Right, Chan B |
 | Sensors     |  Five inputs. Battery, Sensors and markers |  A0..A3 Line/Wall sensors<br>A6 - Start marker sensor<br>A7- battery voltage monitor |
 | Sensor Emitters |  Turn on/off all sensor emitters  |  4 - Digital out  |

That leaves pins 11, 12, A4 and A5. Some kind of user input is desireable and another status LED might be useful. It is unlikely that SPI or I2C is used but it would be sensible to use either 11,12 or A4,A5 for these two pin assignments so that they are easily swapped around should there be a desire to add some other device. Note that any SPI device will probably want two more additional pins for slave select and command/data selection depending on the device.


#### Summary:
#### Revision 1:

* place the motor control lines adjacent
* ensure both PWM signals come from the same timer leaving one timer spare
* place the encoder control lines adjacent
* user LED on pin 6 means that it can be faded - may be useful or just for fun
* possibly only need a single emitter control output but a spare IO exists if they should be split into two groups.
* use six analogue inputs for sensors of any kind
* user button on an analogue input means it could be replaced with a potentiometer or a multi-position switch if that is appropriate for some task.
* pin 12 as a user button would allow an additional sensor or, again, a potentiometer as input.
* battery voltage monitor is essential for good motor control.


 | Pin  |  Purpose                                                       | Fixed |
 |:----:| :-----------------------------------------------------------   | :---: |
 |   0  |  Serial RXD. Used by the bootloader and default serial port    |   Y   |
 |   1  |  Serial TXD. used by the bootloader and default serial port    |   Y   |
 |   2  |  Left Encoder Channel A                                        |   Y   |
 |   3  |  Right Encoder Channel A                                       |   Y   |
 |   4  |  Left Encoder Channel B                                        |   -   |
 |   5  |  Right Encoder Channel B                                       |   -   |
 |   6  |  User Button or LED (can be PWM'ed)                            |   -   |
 |   7  |  Left Motor Direction                                          |   -   |
 |   8  |  Right Motor Direction                                         |   -   |
 |   9  |  Left Motor PWM (OC1A)                                         |   -   |
 |  10  |  Right motor PWM (OC1B)                                        |   -   |
 |  11  |  Emitter on/off                                                |   -   |
 |  12  |  Spare I/O - emitter control, LED, etc                         |   -   |
 |  13  |  SCK and status LED - good for user feedback                   |   Y   |
 |  A0  |  Wall/Line Sensor                                              |   Y   |
 |  A1  |  Wall/Line Sensor                                              |   Y   |
 |  A2  |  Wall/Line Sensor                                              |   Y   |
 |  A3  |  Wall/Line Sensor                                              |   Y   |
 |  A4  |  Sensor? I2C SDA?                                              |   -   |
 |  A5  |  Sensor? I2C SCL?                                              |   -   |
 |  A6  |  Function Select Switches                                      |   -   |
 |  A7  |  Battery Voltage monitor                                       |   Y   |

## IMU

If a builder wants to add a gyro or other IMU, some compromises will be needed. There are just not a lot of IO pins. A Purely analogue gyro can simply be connected to one of the analogue sensor inputs. Aside from losing a sensor input, that is not a great problem. Modern, digital IMUs are a little more difficult. The choices are I2C or SPI.

### I2C

The main advantage of I2C is that only two pins are needed for communication with one or more I2C devices. This makes them very attractive in IO limited systems like this. Users could add several IMUs, displays, LED drivers port expanders or whatever else it desired. the downside is that I2C is not a fast protocol. For the level of performance anticipated from an Arduino robot, this is not likely to be an insurmountable issue although gyros in particular benefit from being read frequently in robots. Using I2C would mean losing two analogue input channels (A4 and A5). These are not currently committed but line follower might be a little more challenging with a maximum of only five analogue inputs and that would mean using pin 12 as a button input.

There are several IMU breakout boards communicating over I2C that can be used with the Arduino. This one - [MinIMU-9 V5](http://www.hobbytronics.co.uk/sensors/imu/minimu-9-v5) - includes gyro, accelerometer and compass on one board together with level shifting electronics for use directly with the Arduino.

### SPI

SPI communications are much faster than I2C and will probably be able to provide data as fast as the user code can request it. It is, however, a very inefficient user of IO pins. A typical SPI device uses at least four pins and each additional device would use another pin for the chip select. Connecting a SPI device to the Arduino Nano would require pins 11, 12, 13 and one other for the chip select. For this application, SPI.

