# Motor Encoders

To measure the motor rotation, the motor shafts are attached to quadrature encoders. The encoders generate a series of pulses on two outputs, Channel A and Channel B, as the motors rotate. The frequency of the pulses increases as the motors turn faster. The pulses are arranged so that they overlap:

````
Clockwise Rotation (CW)        ----->

             -----       -----       -----       -----
Chan A      |     |     |     |     |     |     |     |     |
          --       -----       -----       -----       -----

       --       -----       -----       -----       -----
Chan B   |     |     |     |     |     |     |     |     |     |
          -----       -----       -----       -----       -----

Anticlockwise Rotation (CCW)   <-----

````

These pulses are used to measure the direction of rotation, the speed of the motor and the distance traveled.

## Direction of rotation

As the motor rotates clockwise, the pulses are generated from left to right. Examine the pulses and it is clear that, whenever Channel A changes from low to high, Channel B is always low. Changes from low to high are called **rising edges**. Changes from high to low are caled **falling edges**. Channel A falling edges always correspond to Channel B being high.

If the motor is turning in the opposite direction, counter clockwise, the edges arrive in the reverse direction as well. Now rising edge changes on Channel A have Channel B high while falling edges on Channel A have Channel B low - the opposite of the clockwise results.

A little thought should show that the direction of rotation can be worked out just by examining the state of Channel B when Channel A changes. A table shows the results

|           |  B Low | B High |
|----------:|:------:|:------:|
| A Rising  |   CW   |   CCW  |
| A Falling |   CCW  |   CW   |

So long as the edges can be detected, it is easy enough to work out the direction of rotation.

## Speed of rotation and distance travelled

The speed at which the motor is turning can be measured by counting how many pulses are generated in a fixed time interval. Distance travelled is easily measured by keeping a total of the number of pulses generated. At top speed, the encoder pulses may be generated thousands of times per second and it is important that the processor is able to respond to all of them if the speed is to be measured accurately. It is not practical to have the processor constantly checking the state of the encoder signals to see if they have changed - there would be no time left to do anything else.

## Interrupts

An interrupt is a way for the processor to respond automatically to some condition. Here, a change in the state of the encoder inputs must be detected very quickly. The ATMega328p in the Arduino Nano, like many other processors, can generate an interrupt when changes happen on some of its input pins. Two pins in particular are specifically designed for this job:

>PD2 for INT0  (Arduino Digital Pin 2)

>PD3 for INT1  (Arduino Digital Pin 3)

## Edge Direction

According to the ATMega328p datasheet, section 12:

The INT0 and INT1 interrupts can be triggered by a falling or rising edge or a low level on the associated input pin.

This is set up as indicated in the specification for the External Interrupt Control Register A – EICRA.

The **External Interrupt 0** is activated by the external pin INT0 if the SREG I-flag and the corresponding interrupt mask are set. The level and edges on the external INT0 pin that activate the interrupt are defined as

|ISC01 | ISC00 | Description
|:----:|:-----:|------------|
|  0   |   0   | Low Level of INT0 generates interrupt
|  0   |   1   | Logical change of INT0 generates interrupt
|  1   |   0   | Falling Edge of INT0 generates interrupt
|  1   |   1   | Rising Edge of INT0 generates interrupt


The **External Interrupt 1** is activated by the external pin INT1 if the SREG I-flag and the corresponding interrupt mask are set. The level and edges on the external INT1 pin that activate the interrupt are defined in Table 12-1

|ISC11 | ISC10 | Description
|:----:|:-----:|------------|
|  0   |   0   | Low Level of INT1 generates interrupt
|  0   |   1   | Logical change of INT1 generates interrupt
|  1   |   0   | Falling Edge of INT1 generates interrupt
|  1   |   1   | Rising Edge of INT1 generates interrupt

To enable these interrupts, bits must be set in the external interrupt mask register EIMSK

>EIMSK:INT0 (bit 0) enables the INT0 external interrupt

>EIMSK:INT1 (bit 1) enables the INT1 external interrupt

## Code

The motor encoders are connected to pins 2, 3, 4 and 5. One encoder uses pins 2 and 4, the other encoder uses pins 3 and 5.
To set up the interrupts:

````
  void setup() {
     pinMode(LeftEncA, INPUT);
     pinMode(LeftEncB, INPUT);
     pinMode(RightEncA, INPUT);
     pinMode(RightEncB, INPUT);

     EIMSK |= (1 << INT0) | ( 1 << INT1 );    // Enable both interrupts
     EICRA |= (1 << ISC11) | ( 1 << ISC10 );  // RISING edge INT1
     EICRA |= (1 << ISC01) | ( 1 << ISC00 );  // RISING edge INT0
  }
````

Two interrupt service routines (ISRs) test the encoder inputs and update the gloal counter variables. These may look long and complex but they generate very compact code and each interrupt will use no more than 2 us on an Arduino Nano running at 16MHz. The rapid response is possible because the normal Arduino functions have been replaced with direct access to the hardware. The ISRs maintain two integers for the count related to each encoder.

````
// global constants and variables

const unsigned char leftEdgeDirectionBit = (1 << ISC00);
const unsigned char rightEdgeDirectionBit = (1 << ISC10);

volatile int leftCount;
volatile int rightCount;

ISR( INT0_vect )
{
  int count = leftCount;
  if (EICRA & leftEdgeDirectionBit) {
    if ( PIND & (1 << LeftEncB))  {
      count++;
    } else {
      count --;
    }
    EICRA &= ~leftEdgeDirectionBit;
  } else {
    if ( PIND & (1 << LeftEncB))  {
      count--;
    } else {
      count++;
    }
    EICRA |= leftEdgeDirectionBit;
  }
  leftCount  = count;
}


ISR( INT1_vect )
{
  int count = rightCount;
  if (EICRA & rightEdgeDirectionBit) {
    if ( PIND & (1 << RightEncB))  {
      count++;
    } else {
      count --;
    }
    EICRA &= ~rightEdgeDirectionBit;
  } else {
    if ( PIND & (1 << RightEncB))  {
      count--;
    } else {
      count++;
    }
    EICRA |= rightEdgeDirectionBit;
  }
  rightCount = count;
}
````

## Some performance data

For the Pololu 6 Volt MP gearmotors with 10:1 gear ratio, the encoders generate about 2100 pulses per second at full speed with a 6 Volt motor supply and no load on the motor. Higher gear ratios may reduce the speed because of the increased load.

10:1 is a handy reduction ratio because the stock magnetic encoders generate 6 edges per rotation on Channel A. That means that the frequency recorded is the same as the output shaft RPM. The pololu dta indicates 2200 RPM at 6 Volts so that is probably close enough.

There is a separate page all about the [performance tradeoffs](speed-performance.md).

