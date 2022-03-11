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

#define HOST_ACTION_PERIOD      40


//init threads
rt_thread_t servo_thread_set = RT_NULL;
rt_thread_t servo_thread_calculate = RT_NULL;

//three servomotors could either correspond to a
//array or they could have a dedicated id

//the pseudocode is for spesified id's

void servo_init (void) {

    //THREAD HANDLING
    rt_uint32_t thread_stackSize = 32;
    rt_uint8_t thread_priority = 1;
    rt_uint32_t thread_tick = RT_NULL;

    servo_thread_set = rt_thread_create_periodic("servo_thread_set",
                                                 servo_set_positions,
                                                 RT_NULL,
                                                 thread_stackSize,
                                                 thread_priority,
                                                 thread_tick,
                                                 HOST_ACTION_PERIOD);

    servo_thread_calculate = rt_thread_create_periodic("servo_thread_calculate",
                                                        servo_set_positions,
                                                        RT_NULL,
                                                        thread_stackSize,
                                                        thread_priority,
                                                        thread_tick,
                                                        HOST_ACTION_PERIOD);

    if (servo_thread_set == RT_NULL) { return; }
    if (servo_thread_calculate == RT_NULL) { return; }

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


