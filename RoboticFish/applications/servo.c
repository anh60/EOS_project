/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Contains functionality belonging to the fish' servo motors.
 * There are three servo motors in each joint of the fish' tail.
 * These servo motors requires reading of current position,
 * calculation of new position and setting of the calculated values.
 *
 * This tasks are done using a thread evoked by a timeout.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */
#include "servo.h"
#include <rtthread.h>

//init threads
rt_thread_t servo_thread_set = RT_NULL;
rt_thread_t servo_thread_calculate = RT_NULL;

//three servomotors could either correspond to a
//array or they could have a dedicated id

//the pseudocode is for spesified id's

void servo_init (void) {
    /*INIT TIMER
     * set name
     * set timeout function - call thread
     * set parameter for timeout function (not needed)
     * get time from rt_tick_from_millisecond(rt_uint32_t ms)
     * set timer flag
     * call rt_timer_create
     * call rt_timer_init
     *
     *INIT THREAD
     * set name
     * set entry function of thread
     * set parameters of entry function (not needed?)
     * set stack size
     * set task priority
     * set tick but not needed because no should have same priority
     *
     *START TIMER
    */

    //TIMER HANDLING
    static rt_timer_t servo_timer_set;
    static rt_timer_t servo_timer_calculate;

    //this is in clockticks
    //TODO convert into ms
    int timeout_clockticks = 10;

    servo_timer_set = rt_timer_create("servo_timer_set", servo_timer_set,
                                 RT_NULL, timeout_clockticks,
                                 RT_TIMER_FLAG_PERIODIC);


    //TODO the function evoked should be the thread handling the servo
    servo_timer_calculate = rt_timer_create("servo_timer_calculate", servo_timer_calculate,
                                 RT_NULL, timeout_clockticks,
                                 RT_TIMER_FLAG_PERIODIC);

    //THREAD HANDLING
    rt_uint32_t thread_stackSize = 32;
    rt_uint8_t thread_priority = 1;
    rt_uint32_t thread_tick = RT_NULL;

    servo_thread_set = rt_thread_create("servo_thread_set", servo_set_positions,
                                    RT_NULL, thread_stackSize,
                                    thread_priority, thread_tick);

    servo_thread_calculate = rt_thread_create("servo_thread_calculate", servo_set_positions,
                                    RT_NULL, thread_stackSize,
                                    thread_priority, thread_tick);

    if (servo_thread_set == RT_NULL) { return; }
    if (servo_thread_calculate == RT_NULL) { return; }


    //start the timer
    if (servo_timer != RT_NULL) rt_timer_start(servo_timer_calculate);

    if (servo_timer != RT_NULL) rt_timer_start(servo_timer_set);



    return;

}

//the servo has 10 ms for setting the positions and should
//do this every 40 ms

static void servo_set_positions(int id, int servo_value) {
    //send to device x,y or z

    rt_err_t err = rt_thread_suspend(servo_thread_set);

    if (err != RT_EOK) {
        //some error has occurred, fix
    }

    rt_schedule();

    return;
}

static int servo_calculate_positions(int servo_value) {
    //some math non lo so
    servo_value = servo_value + 1;

    return servo_value;
}


