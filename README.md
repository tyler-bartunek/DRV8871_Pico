# DRV8871_Pico
Implementation of a motor driver class for use with the raspberry pi pico RP2040 board using the Pico SDK. 

## Examples
More examples are coming soon, but for now there is one example complete with all CMakeLists.txt files required for a successful minimal build. You should be able to clone this repository, make a local build directory, and invoke CMake and your make tool of choice (I used mingw) to get a successful build for the given fixed speed code. 

### Pinout in examples

| Pin | Connected Hardware |
| --- | --- |
| 12 | Encoder Channel A |
| 13 | Encoder Channel B |
| 27 | Motor Driver IN1 |
| 28 | Motor Driver IN2 |

## Getting started with this library

Default construction of the DRV8871Motor object: 

```
//Be sure to include the header
#include "drv8871_motor.h"

//Instantiate the object
DRV8871Motor motor;
```

Custom pinout setup:

```
//Be sure to include the header
#include "drv8871_motor.h"

//Instantiate the object
DRV8871Motor motor = DRV8871Motor(uint8_t in1_pin, uint8_t in2_pin, uint8_t encoder_a_pin, uint8_t encoder_b_pin);
```

Parameters:
- `in1_pin`, `in2_pin`: The GPIO connected to your IN1 and IN2 on the DRV8871. Must be on different PWM slices.
- `encoder_a_pin`, `encoder_b_pin`: GPIO connected to the A and B channels on your two-channel encoder on your motor. These pins must be adjacent, and A must be the lower pin number.  

### Typical Operation:

`void init()`

Configures all of the pins to operate the way they are meant to, attaches your encoder object (an instance of adamgreen's QuadratureDecoder object), and sets the PWM frequency to a default frequency of 1 kHz.  

`void drive(int speed_command)`
This method is where the magic happens. Drives the motor and updates both the encoder counts (raw count) and speed estimate (rad/s). 

Parameters:
- `speed_command`: Integer value between -10000 and 10000 (percentage duty cycle multiplied by 100). 

### Setter methods

`void set_pwm_frequency(uint8_t pin_1, uint8_t pin_2, uint8_t divider, uint32_t frequency);`

Sets the wrap member variable for PWM for you to hit a target PWM frequency. By default, this is set to 1 kHz in `init()`.

Parameters:
- `pin_1`, `pin_2`: GPIO pins for which you want to adjust the PWM frequency. Must be on different PWM slices. 
- `divider`: Clock prescaler for the system clock for PWM.
- `frequency`: Desired frequency for PWM to operate at.

`void set_encoder_filter_parameter(float new_alpha);`

Sets the value for the weighted average filter in speed calculations, on the range of 0 to 1. The minimum value corresponds to not accepting new speed readings, the maximum corresponds to filtering being disabled. Default is to have the filtering disabled. 

Parameters:
- `new_alpha`: New filter parameter, must be on the interval of 0 to 1. 

`void set_gear_ratio(float ratio);`

Sets the gear ratio for your motor for speed calculations. Default is 19.

Parameters:
- `ratio`: Number of turns of the motor for one revolution of the output.  

`void set_counts_per_rev(float new_counts_per_rev);`

Sets the number of counts per revolution for your two-channel encoder. Default is 44, and was for an encoder that has 11 counts per channel in a revolution. Since this uses quadrature encoding, you multiply this by 4 to get 44. 

Parameters:
- `new_counts_per_rev`: The number of quadrature counts per revolution for your motor. 