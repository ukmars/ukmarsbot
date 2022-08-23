# Line Sensor Basic
## Contents

In this folder you will find:

 - images of the various sensor board versions
 - schematic drawings for each as PDF files
 - bill of material spreadsheets with component values. Some components are adjust on test or may be substituted by builders. Suggestions are given but not guaranteed to be correct.
 - zipped gerbers suitable for uploading to board manufacturers

## Notes

The basic line sensor board is intended for the full-size classic line following and drag race events. 

### Version 20190815C

Changes some component types and provides better pad sizes to make soldering easier. __Use this version for preference__

### Version 20190815A

This version will attach to the front of the robot with the emitters and detectors mounted underneath, pointing at the floor. Connection to the mainboard is via a multiway connector to the sensor pin headers on the mainboard.  

The two line detectors straddle the edges of the line and point directly downwards.

The turn and finish markers are placed at the outer edges of the board and will be angled slightly outwards. The board width has been constrained to 100mm so that it fits the limits of the popular low cost board manufacturers as well as the maximum dimension permitted by the free edition of Eagle.

A single transistor is available to turn on and off the emitters if that is desired. Alternatively, the transistor can be omitted and a wire link substituted so that the emitters are always on.

A header, J2, is provided so that builders can experiment with different load resistor values for the two line sensors.

Two indicator LEDs are also available for user feedback.

The emitter and indicator output pin assignments correspond with those on the wall sensor board.

In use the line sensor board will overhang the front of the robot and extend to either side. Builders may find that the steering control of the mouse in this configuration will be different to that in the maze sensor configuration.

