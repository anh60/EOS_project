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

#define THREAD_PRIORITY         3
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        1

#define TIMEOUT_SET             10
#define TIMEOUT_CALCULATE       45

//init threads
rt_thread_t servo_thread_set = RT_NULL;
rt_thread_t servo_thread_calculate = RT_NULL;


struct servo_motor servo;

int servo_init (void) {

    //TIMER HANDLING
    //static rt_timer_t servo_timer_init;
    /*servo_timer_init = rt_timer_create("servo_timer_init",
                                     servo_timer_set,
                                     RT_NULL,
                                     timeout_clockticks,
                                     RT_TIMER_FLAG_PERIODIC);
    */

    rt_timer_t servo_timer_set = rt_timer_create("servo_timer_set",
                                      start_thread_1,
                                      RT_NULL,
                                      TIMEOUT_SET,
                                      (/*RT_TIMER_FLAG_SOFT_TIMER ||*/ RT_TIMER_FLAG_PERIODIC));


    //TODO the function evoked should be the thread handling the servo
    rt_timer_t servo_timer_calculate = rt_timer_create("servo_timer_calculate",
                                            start_thread_2,
                                            RT_NULL,
                                            TIMEOUT_CALCULATE,
                                            (/*RT_TIMER_FLAG_SOFT_TIMER ||*/ RT_TIMER_FLAG_PERIODIC));

    //THREAD HANDLING
    servo.servo_thread_set = rt_thread_create("servo_thread_set",
                                        servo_set_positions,
                                        &servo,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY,
                                        THREAD_TIMESLICE);

    servo.servo_thread_calculate = rt_thread_create("servo_thread_calculate",
                                               servo_calculate_positions,
                                               &servo,
                                               THREAD_STACK_SIZE,
                                               THREAD_PRIORITY,
                                               THREAD_TIMESLICE);


    if (servo.servo_thread_set == RT_NULL) { return -2; }
    if (servo.servo_thread_calculate == RT_NULL) { return -2; }

    rt_err_t err = rt_timer_start(servo_timer_set);
    if (err != 0){ return -1;}

    err = rt_timer_start(servo_timer_calculate);
    if (err != 0){ return -1;}

    return 0;

}

static void servo_set_positions(void *param) {

    rt_err_t err = rt_thread_suspend(servo.servo_thread_set);

    if (err != RT_EOK) { /*some error has occurred, fix*/ }

    rt_schedule();

    return;
}

static void servo_calculate_positions(void *param) {
    struct servo_motor *servo = param;

    servo->servo_value[0] = 0;
    servo->servo_value[1] = 1;
    servo->servo_value[2] = 2;


    rt_err_t err = rt_thread_suspend(servo->servo_thread_calculate);

    if (err != RT_EOK) { /*some error has occurred, fix*/ }

    rt_schedule();

}

static void start_thread_1(void *param){
    rt_thread_startup(servo.servo_thread_set);
    return;
}

static void start_thread_2(void *param){
    rt_thread_startup(servo.servo_thread_calculate);
    return;
}


