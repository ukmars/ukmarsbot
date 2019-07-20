# UKMARSBOT Specification

* This is an entry level robot able to be built by adults, students or schoolchildren from readily available parts that are likely to remain available for several years using the provided PCBs with minimal tools and expected skill levels. Some soldering is expected but not of small Surface Mount Devices (SMDs).

* The same PCBs can be populated with minimal parts to enable simple robot competition challenges to be accomplished, or enhanced with additional or different parts to enable more difficult challenges to be met.

* The robot should be able to compete in and meet the constraints of UK robot competitions such as those held by UKMARS, the IET or Polulo that feature:

  * Line following of white or black lines
  * Drag race
  * Non-contact wall following
  * Maze solving


* There should be a means of selecting a number of program options – 4 as a minimum and a way of showing which is being run. This could be a number of LEDs or other type of display. At least one start run button and one other control push button should be available.

* Separate sensors must be able to be easily attached and removed to cope with the requirements of different competition challenges. It would also be advantageous to enable wheels to be swapped for different size ones for different challenges.

* The size of the basic robot needs to be able to fit and manoeuvre easily within a 16.8 x 16.8cm maze cell. Ideally measuring no more than 85mm wide and 110mm long with rounded corners. The robot may be wider than these dimensions if wheels with a diameter greater than 32mm are selected.

* The robot must have multiple mechanical fixing points to allow flexible options for sensors and additional hardware to be securely mounted as well as motor fixing points.

* The robot should be powered by simple rechargeable battery of between 7 and 12 volts requiring no expensive charging equipment. An analogue sensor should be available to monitor the battery voltage. There should be a switch or other means of isolating the battery and a diode for polarity protection.

* The robot should be controlled by a small form factor microcontroller with adequate pins and functionality on the pins to read sensors and control the wheel speeds using PWM. This micro-controller should be supported by an easy to use and free development environment which can easily be installed on a Windows, MAC or Linux PC.

## Consequences of specifications – design ideas

* Motors will have to be N20 micro metal gearbox motors – required to meet IET and Polulo contest rules – but specific motor power and gearing ratio can be chosen by the user. A gearing of 20:1 for the motor would be a good initial choice.

* Space should be available for extended shaft motor option so that encoders can be added if required. With these extended shaft motors back to back the PCB will be 6.5cm wide. Wheels are 1 cm wide giving a total width of 8.5cm.

* We will need to have a separate plug in board for the wall sensors and one for the line following sensors

* Motor driver H bridges could be a chip such as L293D or a plug in board such as the L9110 or TB6612FNG board. Other choices are available.

* The most suitable microcontroller is an Arduino Nano R3 as it has enough IO pins (22) of the right types. It is recommended to be programmed using the standard Arduino IDE to develop code. A recommended specification of pin usage will be provided with a sample Arduino sketches that demonstrate how to set up these pins correctly.
