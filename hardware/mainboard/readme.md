# UKMARSBOT mainboard

## Contents

In this folder you will find:

 - images of the various mainboard versions
 - schematic drawings for each as PDF files
 - bill of material spreadsheets with comonent values. Some components are adjust on test or may be substituted by builders. Suggestions are given but not guaranteed to be correct.
 - zipped gerbers suitable for uploading to board manufacturers

## Mainboard ##

The mainboard serves to form the chassis of the robot and to wire together the modules - the processor, the motor driver and the sensor board.

In its basic configuration, the robot would be driven by two Pololu micrometal gearmotors or equivalen. The board can accomodate wheels of diameter up to approximately 35mm if the standard Pololu motor mounts are used. Substituting Pololu extended mounts will move the motors outboard by an amount sufficient to allow larger wheels of up to 70mm.

There is space between the motors to allow the use of the Pololu magnetic encoders or some equivalent so that feedback is available for speed or positional control.

Clearly, the diameter of the drive wheels will determine the ride height of the board. Builders have the option to implement their own schemes for anti-tipping skids usingthe 3.2mm holes at front and rear.

Alternatively, spacers can be placed between the motor mounts and the PCB to raise the motors and keep the ride height low. For a range of common wheel sizes, we will provide drawings and STL files for suitable risers. Where facilities are available, risers can be made from laser cut plywood/acrylic or fabricated with 3D printers or CNC milling machines. In many cases, standard thicknesses of common materials like plywood and MDF, simply cut out and drilled will make excellent risers.

A single sheet of material forming a kind of strap across the top of the motors will provide additional stiffness and may serve as a suitable platform for addition peripherals such as I2C gyros, displays and bluetooth boards. A camera could be fitted for recording runs or even as part of a remote control system when used with a bluetooth board.

Sample STL files for these parts are available in the 'mechanical' folder.

## Balance ##

It is all but impossible to ensure at this stage that the robot will be well balanced. Batteries vary in weight by a factor of more than 2 and the builder will have to ensure that the correct posture is maintained either by the use of suitable skids or, if necessary, counterweights.

## Battery

The space at the rear is intended for a PP3 size battery with a voltage in the range 7-9 Volts. These may be dry cells or rechargeable NiMh or LiIon cells. Any of these are suitable.

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