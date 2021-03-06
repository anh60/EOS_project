# Implementation of robotic fish using RT-Thread on STM32F401

## Specifications
Our goal is to make an autonomous robot fish with sensors and three servo motors.
We are using the STM32F401 Nucleo 64 board because this can provide us with two ADCs 
and option for PWM. 
| Task		                                          | Real time constraint | Time constraint |
| ------------------------------------------------- | -------------------- |---------------- |
| Read and store data from temp. sensor             | soft                 | 100 ms          |
| Read and store data from pressure sensor          | soft                 | 75 ms           |
| Calculate servo pos. from degrees to digital value| hard                 | 13 ms**         |
| Set three servo motor positions simultaneously    | hard                 | 10 ms*          |
| Error handling for extreme temperatures           | hard                 | aperiodic       |

*  The hard time constraint of calculating and setting the servo motors positions should take no longer than 50 ms as the microcontroller sets the servos position every 50 ms. This corresponds to having a resolution of five steps on the servo motors with a speed of 2 Hz. 
** As the microcontroller needs to calculate three positions in a time frame of 40ms (50 ms – 10 ms already reserved by setting servo positions) the calculation task needs a hard time constraint of 13 ms.

Our expected inputs:
-	Analog values from pressure and temperature sensors to the microcontroller which uses the ADC to make the values for the tasks digital. 

and expected outputs:
-	Three PWM signals for the servo motors.

## Modules 
We have divided the system into modules based on the tasks they are performing. A natural partitioning was therefore the different sensors.  Each module is again represented by one or more threads initialized by the main function which is the centrepiece of the design. 

In modules where it is necessary that independent threads share information this is done using shared variables passed around in objects containing the threads and variables in question. 

### Pressure sensor
According to the specifications the pressure sensor should be read and the reading stored to flash memory every 75 ms. The tasks are completed by a single thread containing a handler. A timer is set up to trigger an event. When the event is set the thread state is changed from suspended to ready state. 
When the handler is executed the pressure readings are generated as mock data using a random integer generator. This reading is passed on to a function using the built-in flash library to store data to the eight and last flash sector of the microprocessor. 
When inspecting the memory the data can appear wrong, but this is simply the nature of storage in flash memory. The data is stored byte by byte using another edian. If we were to read it out of the memory again as a part of the OS tasks we would simply do a byte swap to reproduce the results. 

### Servo motor
In the specification it is stated that there are three separate servo motors that requires to be converted from a pre-planned route of values representing degree to voltage levels. After converting the angular values the input of the individual motors should be set. The setting of positions is required to take a maximum of 10 ms and has a period of 50 ms. The remaining 40 ms should be used to calculate the values meaning it is a maximum of 13 ms per calculation.

The servo motor module is composed by two individual threads. One for calculating the servo positions and one for setting the actual values. Each of the threads are connected to its own timer and event in the same way as the pressure sensor. 
To communicate between the two threads a servo motor object is created in the initialization function. This object contains the threads and an array to store the values of the motors. The object is passed as a parameter when the threads are started.

If the thread calculating the servo positions misses its deadlines the motor should apply the same values as of the last period to avoid unnecessary glitching in the fins of the fish. 

### Temperature sensor

The temperature sensor is built in the same way as the pressure sensor where mock data is read as from a temperature sensor and then stored to the flash memory of the mcu. In this case two separate thread are used to handle the reading and storing. The value of the temperature is set to range between 0-256 meaning it is represented on eigth bits. Both these tasks are periodic and triggered every 100 ms with a soft deadline.  

When a temperature above 200 degrees Celsius is detected, the read_temp thread initializes and starts up an aperiodic task to handle the temperature irregularity executed by a thread extr_temp. This is done by .. . When the error handling is finished the thread is deleted. 

## Testing 

 A project requirement was to exhaust the system in some way. To benchmark the system CPU usage was chosen as the parameter. To measure the usage we used https://github.com/RT-Thread/rt-thread/blob/9bc3896e41716f6415e948ffea153a5453fe4b34/bsp/mb9bf500r/cpuusage.c as inspiration. 

 - How often do we measure?
 - What is the working principle?

 The module collects the simulated measurements and saves it to a file. This file is in turn read by a python script that calculates the average cpu usage, trends in time and standard deviation. 

## Operative system enhancement 

Another requirement was that the system should be composed by both periodic and aperiodic tasks. In RT-thread a task is most easily considered a thread. A thread is created before its startup. When the thread is entered it performs a user-defined function. As this function is complete the thread is deleted. 

As the periodic tasks was implemented there was a clear need to implement an easier solution than a combination of timers, threads and events to obtain this functionality. As a result the group decided to implement the possibility of periodic tasks defined like a one-shot task but with a user-defined period. 

This is done by ... 
