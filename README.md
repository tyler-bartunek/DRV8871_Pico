# DRV8871_Pico
Implementation of a motor driver class for use with the raspberry pi pico RP2040 board using the Pico SDK. 

## How it works
You begin by instantiating a DRV8871Motor object with either the default constructor, as is done in the provided example, or using the constructor to specify your motor control and encoder pins. 

So for the default constructor, all you do is 
```
DRV8871Motor motor;
```

If you do choose to set your own pin numbers, do note that the following requirements must be met:

- IN1 and IN2 must be on different PWM slices
- ENC_A and ENC_B (your two encoder channel pins) must be on adjacent pins. 

### init
Before your DRV8871Motor object is ready to rock and roll, however, you do need to invoke its init method. This configures all of the pins to operate the way they are meant to, and also attaches your encoder object (an instance of adamgreen's QuadratureDecoder object). 

### drive
This method is where the magic happens. 

Feed it any integer value between -10000 and 10000, and it will drive either forward or in reverse at that given PWM level. No muss, no fuss. It just runs and updates the encoder counts and speed in rad/s as it goes. 

Why 10000? Well, that's a percentage multiplied by 100, so you can specify the percent duty cycle out to two decimal places. 

### Setter methods
The speed in rad/s is predicated upon a fixed gear ratio and counts per revolution. You can change these settings from the defaults of 19 and 44 respectively to reflect your motor choice. You do this with 

```
motor.set_gear_ratio(new_ratio);
motor.set_counts_per_rev(new_cpr);
```

where new_ratio and new_cpr are float values representing your new gear ratio and counts per rev. 

So for the motor inspiring the defaults, these values refer to a 19:1 reduction and a single channel of the dual-channel encoder counting 11 pulses per revolution. Since this library uses quadrature encoding, you actually get 4 times as many counts. Thus, 44 counts per revolution in that case.

Additionally, the speed measurements are generally noisy (as is the case for all numerical differentiation). The `get_speed()` method that is called internally to compute the motor's speed actually has a weighted average filter implemented, and you can change the weight in that filter from the default of 1 (trust new measurements implicitly) using `set_encoder_filter_parameter`. 

```
//As an example.
motor.set_encoder_filter_parameter(0.01);
```

## Examples
More examples are coming soon, but for now there is one example complete with all CMakeLists.txt files required for a successful minimal build. You should be able to clone this repository, make a local build directory, and invoke CMake and your make tool of choice (I used mingw) to get a successful build for the given fixed speed code. 
