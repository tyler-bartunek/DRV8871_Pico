/*
Code for testing that we can run a motor using the DRV8871 motor driver with the Pico. 
The motor is connected to the DRV8871, and the DRV8871 is connected to the Pico. 

This test does not run the motor. Rather, it just prints out the counts and speed 

Author: Tyler Bartunek
*/

//Basic includes for the Pico SDK
#include "pico/stdlib.h"

//Add iostream for IO operations for being able to print out values in differing cases
#include <iostream>

//Include the header file for the DRV8871 motor driver library: star of the show
#include "drv8871_motor.h"

DRV8871Motor motor = DRV8871Motor(); //Create an instance of the DRV8871Motor class

int main() {

    stdio_init_all(); //Initialize all standard IO
    sleep_ms(2000); //Sleep for a short time to allow the user to see the output from stdio_init_all() before the motor starts running

    //Call the motor's initialization function to set up the GPIO pins and PWM for controlling the motor
    motor.init();

    //Set the motor's alpha for the weighted average filter: 0.001 determined from Arduino test
    //0.01 might be acceptable, depending on your use-case.
    motor.set_encoder_filter_parameter(0.001);


    //Print the speed we have set the motor to
    std::cout << "Running unpowered encoder test." << std::endl;

    while (true) {
        
        //Drive the motor at the specified speed, provided that is our goal. Otherwise, just get the counts and speed readings.
        motor.get_encoder_counts();
        motor.get_speed();

        //Print out the current speed
        std::cout << "Current counts: " << motor.counts << " Current speed: " << motor.speed << std::endl;
    }

}
