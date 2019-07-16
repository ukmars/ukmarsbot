# Analogue Input on the Arduino Nano

The Arduino software provides a convenient function for reading the analogue input pints, A0-A7. Be aware that analogue input is pretty slow on the Arduino by default. Reading a single channel can take 100us even if the task is not interrupted by anything else. Add at least another 10us if the result is to be simply converted to a floating point value.

The Arduino initialisation code sets the ADC prescaler to its highest value, dividing the system clock by 128 to get an ADC clock of 125kHz. A normal conversion will take no more than 25 clock cycles for the first conversion and 13 cycles therafter.

The designers of the Arduino system probably wanted to make sure that the analogue conversions were at their most reliable possible settings. It is possible to reduce the prescaler to get significantly faster conversions. For most analogues sources this is unlikely to be a problem but there will be some inaccuracies introduced if the ADC is run too fast with high impedance sources. There are also some overheads in the analogRead() function that make it not worth trying to run the ADC too fast.

Aside from any issues with the sample time, the AVR statsheet warns that there will be increased noise if the ADC clock is too fast. the datasheet is not too clear on the relationship between noise and clock speed but it does suggest that, for the full 10 bit resolution, the clock should not be faster than 200kHz. That corresponds to a prescaler set to no less than 80 for a 16MHz part.

So - speeding up the ADC has some drawbacks as far as accuracy and noise are concerned. If compromises with these are justified in order to get faster readings, then it is easy enough to adjust.

## Crosstalk

When multiple channels are connected to an ADC and thed read in quick successsion, care must be taken that the various channels do not interfere with each other. This is not just a question of board layout and sources of noise. Each chanel in turn is connected to the same input circuit inside the processor. If the analogue source has a high impedance, the reading can be influenced by the previous channel voltage.

## ADCSR - The Analogue Control and Status Register

The bottom three bits of ADCSR, determine the prescaler factor. The time shown is for a single conversion to a floating point value with this line of code:

     battery = analogRead(A7) * 4.8828; // 5000/1024

The variance is calculated over 10000 samples with the analogue input set to as close as possible to 2.5V with a potentiometer. Variance is directly related to the ammount of noise in the result.

The time taken for each call is measured by setting and clearing a port pin by direct port manipulation to reduce overhead as much as possible. The length of the resulting pulse is measured on an oscilloscope.

## Results

|ADPS2|ADPS1|ADPS0|Divisor|analogRead()| Variance |
|:---:|:---:|:---:|------:|-----------:|---------:|
|  0  |  0  |  0  |   2   |     16 us  |         -|
|  0  |  0  |  1  |   2   |     16 us  |         -|
|  0  |  1  |  0  |   4   |     18 us  |195.0493  |
|  0  |  1  |  1  |   8   |     22 us  | 18.9510  |
|  1  |  0  |  0  |  16   |     28 us  |  1.0999  |
|  1  |  0  |  1  |  32   |     43 us  |  0.4864  |
|  1  |  1  |  0  |  64   |     68 us  |  0.2682  |
|  1  |  1  |  1  | 128   |    120 us  |  0.3425  |

Normally all three bits are set to 1.

Clearly, the conversions are less accurate as the ADC clock increases. By the time the divisor is down to 8 (ADC clock = 2MHz), the ADC is working at no more than 8 bits of useful resolution. If that is enough for the application then it will be reasonably effective. Some accuracy can be recovered if the results are filtered with a moving average or exponential filter.

For a good compromise between accuracy and speed, with source impedances around 5 kOhm, a prescale of 16 is likely to be adequate giving conversions in about 1/6 of the default time. Tht means it is possible to sample all 8 channels on an Arduino Nano in not much more time than it would have taken for one channel using the default setup.

Sample time is not linearly related to ADC clock frequency because of the overhead in the Arduino calls. On the test rig, it was not possible to get conversions at all using the lowest divisor settings and the Arduino analogRead function.

