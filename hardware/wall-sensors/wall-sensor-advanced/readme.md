
## Advanced Wall Sensors V1.2

_No previous versions have been released_

The advanced wall sensor uses four emitter-detector pairs. Two for the side walls and two looking forwards.

The side sensors are used just as they would be in the basic wall sensor. 

Using a pair of sensors for the wall ahead brings advantages and disadvantages.

### Advantages

A pair of forward sensors makes it possible to navigate down a diagonal path and have some chance of avoiding collisions with the posts. They also provide advanced warning of possible collisions on orthoganal runs where there are no walls on either side. Normally they will get little or no response from the posts so any response they do get means something is in the way.

Another benefit is that the combined signals can be used to help align the robot perpendicular to a wall ahead. This can be very useful when searching to correct any turning errors. Also, the paired sensors help to reduce the effect of peaky responses from shiny walls. 

### Disadvantages

Forward facing sensors placed at the sides of the robot will be more likely to see light reflected by any side walls if present. That is, with the robot at some fixed distance from a wall ahead, the sensor will see a slightly larger signal if there is also a wall on the same side.

Always make sure your sensor are adequately shielded from abmbient illumination and direct illumination from the emitters.

## Pairing

You will see that the forward emitters are connected together to one transistor and the side emitters are connected together on another transistor. This arrangement lets you turn on only the forward or only the side emitters. Not only does this reduce the load on the power supply, it helps avoid crosstalk. that is, you do not want the detectors of one type to see light meant for the other type.

## Wall detection

Once calibrated you can determine the presence of a side wall relatively easily. Reliably detecting a wall ahead can be more challenging with a pair of forward sensors. Under most circumstances, you can just add up the responses from both of them and use the resultant value as you might with a single sensor. Note, however, that if you are misaligned, these forward sensors may get a good response from a post on one side even if tghere is no wall directly ahead. 

## Alignment against a wall ahead

If there is a wall in front of your robot, it can get a good steering error by calculating the difference between left and right and dividing that by their sum. This greatly reduces the effect of distance. Withot that, the error magnitude would change with distance and steering becomes unreliable.

## Indicator

A single indicator LED is available for user feedback.


