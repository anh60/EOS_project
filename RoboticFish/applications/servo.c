/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */

#include "servo.h"
#include <rtthread.h>
#include <stdlib.h>
#include "drv_common.h"

struct servo_motor servo;

/**
 * @brief Function to convert predefined degree measurements to PWM signals that can be applied to
 *        a servomotor. Resolution is set to
 *
 * @param int value in degrees to be converted to PWM duty cycles
 * @param int resolution measured in
 *
 * @return int PWM duty cycle
 */
static int degToPWM(int valDeg)
{
    //0 = 500 us
    //180 = 2500 us
    // theoretical precision to 0.09

    int pwm = (valDeg / 0.09) + 500;

    return pwm;
}


static void servo_set_positions(void *param)
{

    // TODO find error handling if no new input has been given 

    //set set voltage signals based on servo_value array


}

/**
 * @brief Function calculating the voltage level that should be applied to
 *        the servo motors given a predefined measurement in dregrees. The function
 *        changes the value of the servo_value array of the servo object passed
 *        as parameter.
 *
 * @param param servo object.
 */
static void servo_calculate_positions(void *param)
{
    struct servo_motor *servo = param;
    static int index = 0;
    // This is the first delay to synchronize the execution of the two threads
    //rt_thread_delay(40 * TICKS_MS);

    // A possibility is to open a file and read from it or can it just be retrived from prog.mem
    // need to produce a PWM signal from degrees to ms

    //Create random values for next revolution (does not make sense, for demonstration only)
    if(index == 0)
    {
        for(int this_servo = 0; this_servo < TOTAL_SERVO_MOTORS; this_servo++)
        {
            for(int this_step = 0; this_step < STEPS_PER_REVOLUTION; this_step++)
            {   //Dummy data in degrees
                servo->servo_value_degrees[this_servo][this_step] = rand() % 180;
            }
        }
    }

    //set pwm value for all motors
    for(int this_servo = 0; this_servo < TOTAL_SERVO_MOTORS; this_servo++)
    {
        servo->servo_value_pwm[this_servo] = degToPWM(servo->servo_value_degrees[this_servo][index]);
    }

    index = (index + 1) % STEPS_PER_REVOLUTION;

}

/**
 * @brief Initializes all necessary threads, timers and events to run the task as well as starting
 *        the timer and threads. Also has a simple error handling.
 *
 * @return int
 *         0  - no errors
 *         -1 - error in timer startups
 *         -2 - error in thread creation
 *         -3 - error in thread startup
 */
servo_motor_t servo_init (void)
{

    /* Initialize sensor variables */
    for(int this_servo = 0; this_servo < TOTAL_SERVO_MOTORS; this_servo++)
    {
        servo.servo_value_pwm[this_servo] = 0;

        for(int this_step = 0; this_step < STEPS_PER_REVOLUTION; this_step++)
        {
            servo.servo_value_degrees[this_servo][this_step] = 0;
        }

    }
    /* Initialize base variables */
    servo.base.active_threads                     = 0;
    servo.base.function_pointers[TOTAL_THREADS-1] = servo_calculate_positions;
    servo.base.function_pointers[TOTAL_THREADS-2] = servo_set_positions;
    servo.base.action_period[TOTAL_THREADS-1]     = CALCULATE_POS_ACTION_PERIOD;
    servo.base.action_period[TOTAL_THREADS-2]     = SET_POS_ACTION_PERIOD;


    // THREAD HANDLING
    servo.base.threads[TOTAL_THREADS-1] = rt_thread_create("servo_thread_calculate",
                                        next_periodic_thread,
                                        &servo,
                                        CALCULATE_POS_THREAD_STACK_SIZE,
                                        CALCULATE_POS_THREAD_PRIORITY,
                                        CALCULATE_POS_THREAD_TIMESLICE);

    servo.base.threads[TOTAL_THREADS-2]  = rt_thread_create("servo_thread_set",
                                         next_periodic_thread,
                                         &servo,
                                         SET_POS_THREAD_STACK_SIZE,
                                         SET_POS_THREAD_PRIORITY,
                                         SET_POS_THREAD_TIMESLICE);

    if(!servo.base.threads[TOTAL_THREADS-1])
            return RT_NULL;

    if(!servo.base.threads[TOTAL_THREADS-2])
            return RT_NULL;

    return &servo;
}

/**
 * @brief Function to set positions of the servo motors given the input
 *        from the calculation thread. If the calculation thread has not
 *        yet provided a new result the old result should be applied again.
 *
 * @param param servo object.
 */

void servo_start(void *param)
{
    struct servo_motor *servo = param;

    rt_thread_startup(servo->base.threads[TOTAL_THREADS-1]);
    rt_thread_startup(servo->base.threads[TOTAL_THREADS-2]);

}
