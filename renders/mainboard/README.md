The images currently in this directory are for illustration, and do not necessarily form part of the documentation.

Full Eagle files and PDF schematics are to be found in the eagle directory.

Meanwhile, these files are presented for discussion and should not be regarded as definitive.

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

## Battery ##

The space at the rear is intended for a PP3 size battery with a voltage in the range 7-9 Volts. These may be dry cells or rechargeable NiMh or LiIon cells. Any of these are suitable.

