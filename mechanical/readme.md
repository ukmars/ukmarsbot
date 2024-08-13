# Mechanical drawings and part files

 In this section you can find STL files for several parts that you can print to help in the assembly of your robot.
## Motor mounts

While the normal Pololu motor mounts will work just fine for UKMARSBOT, you might want to consider custom mounts. The motor mounts here are compatible with the Pololu and Pimoroni motors and there are also alternatives that let you mount the motors a bit further outboard if desired.

With standard 32mm wheels, the robot will be a long awy off the ground. The simple solution is to add some kind of spacer under the motors so that they stand further off the main PCB. there are several spacers here. The 5mm might be too short but it is a good starting point. Your 3D printer slicing software will almost certainly have an option to scale a part in the Z direction so it should be a simple matter to adjust the spacer height until you get just the clearance you are looking for.

Remember that standard M3 round head screws have a head height of 1.7mm or so and that your robot should be able to climb over a step of 1.5mm without the wheels losing grip or any mounting holes getting caught up.

The motor mounting holes in the main PCB are not sized for M3 scres as the screws provided with the commercial mounts are smaller. If you use M3 hardware, you will need to open up the holes with a drill. Clearance for M3 is 3.2mm but actual screws are almost guarandeed to have an outside diameter of less than 3mm so a 3mm drill bit should provide a good locating fit that will help stop the motors moving around if they get a knock.

## Sensor Guards

There are a couple of STL files for sensor guards to be used with the mini-wide sensor board and the 1.3a mainboad. 

[line sensor](marker-sensor-guide-mini-wide.stl)

[marker sensor](sensor-guard-mini-wide.stl)

These are meant to fit over the emitter and detector cases under the sensor board and force the devices indo proper alignment so that they are evenly spaced and correctly positioned over the mainboard slot. To use, print the parts in black, opaque filament and place them down on the bench. The long slot in the guard should be downwards. You can do the main sensor block and each of the marker blocks in separate operations. Insert the emitters and detectors in the sensor board but do not solder them in place. Now fit the guard block guard on the board, over the emitters and detectors so that the surface that was uppermost is now against the pcb. Turn the whole lot over so that the guard block rests agains the bench once more and push the emitters and detectors down into their holes. They should all end up at the same height. Practice this until you are sure you have it right. Now you can solder in the devices and it will be possible to remove the guard block if you wish. 

The blocks are sized so that they completely fill the space between the bottom og the sensor board and the top of the mainboard.
