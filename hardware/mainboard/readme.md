# UKMARSBOT mainboard

## Contents

In this folder you will find:

 - images of the various mainboard versions
 - schematic drawings for each as PDF files
 - bill of material spreadsheets with comonent values. Some components are adjust on test or may be substituted by builders. Suggestions are given but not guaranteed to be correct.
 - zipped gerbers suitable for uploading to board manufacturers
 - 
## Versions

### V1.0 (_UKMARSBOT 20190804A_)

The original, V1.0, mainboard was released in 2019 and was intended to be a prototype for testing. By the time we had built some test robots, there were enough V1.0 boards already in the wild that it became the de-facto standard in spite of a few shortcomings.

### V1.1 (_UKMARSBOT 20210924_)

In 2021, one of our members, David Hannaford fixed up a couple of the more annoying issues on the board. That board became V1.1 and a number are in circulation. The fixes in V1.1 include modification of the serial port and addition of components to allow direct connection of a typical HC05 or HC06 Bluetooth Classic Serial adaptor. _Before connecting a serial device, check the board version to make sure the connections are correct._ No harm should come from using the wrong pinouts but it certainly will not work as advertised.

### V1.2
Does not exist. I skipped a version number by mistake :(

### V1.3 (_UKMARSBOT V1.3_)

Currently in alpha testing, V1.3 was produced in 2022. This version incorporates the changes needed in V1.1 and adds some openings at the front of the board so that builders can experiment with line sensors for the half-size line follower event where the track markers are harder for the robot to see. The design overall remains electrically the same as V1.1 and has been transferred to the KiCad EDA suite to provide better platform independence for developers. 

The board layout has been tidied up a little and the serial connector has moved back by a small amount to prevent the possibility of an HC05/06 interfering with any sensor boards. Note that the pads for the battery retaining clips have been removed to reduce confusion during assembly. Self-adhesive hook-and-loop fastening tape is adequate to retain the battery.

Pad sizes throughout have been increased to make soldering less challenging for those with less experience and older tools.