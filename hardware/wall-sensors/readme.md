# UKMARSBOT Wall Sensors

Wall sensors are intended to be used by robots built to run in micromouse maze-based events such as the wall-follower and maze solving classes.

You can find out more about the various contest classes at https://ukmars.org/contests/

## Contents

In this folder you will find:

 - images of the various sensor baord versions
 - schematic drawings for each as PDF files
 - bill of material spreadsheets with comonent values. Some components are adjust on test or may be substituted by builders. Suggestions are given but not guaranteed to be correct.
 - zipped gerbers suitable for uploading to board manufacturers

## Basic Wall Sensors (20190815A)

The basic wall sensor board has three pairs of emitters and detectors. One pair points directly forwards to measure the distance to a wall ahead if there is one.

The two side sensors allow the robot to steer accurately in the maze and detect the presence of absence of a wall to either side. Both sensors will need to be used when following the IET figure eight maze course. For simple left- or right-wall following one or other side sensor can be omitted.

The basic wall sensor board is intended for wall following events in the classic micromouse maze. While it could be used for maze solving, a slightly more sophisticated board with four sensors is likely to give better results.

The emitters are placed above the board and the detectors are below. When mounted, the sensor board will need to be raised above the main board so that there is room for the detectors between the sensor board and the main board. Placing the detectors like this will shield them both from ambient light and direct illumination by the emitters.

A single transistor is available to turn the emitters on and off. There is no provision to bypass this because the wall sensors are much less reliable if used with the emitters continuously illuminated. Furthermore, the higher currents needed by wall sensors would place an unacceptable load on the power supply if the emitters were left on continually.

Two visible LEDs are available for user feedback.

The emitter and indicator output pin assignments correspond with those on the line sensor board.

The sensor board does not overhang the mainboard outline ad so will not interfere with motion insde the maze. Builders may find that the steering control of the mouse in this configuration will be different to that in the line sensor configuration.

Values for the load and current limit resistors have not been entered because the circuit has not yet been tested in this configuration. A trial is underway and suggested starting values will be given when that is done.

