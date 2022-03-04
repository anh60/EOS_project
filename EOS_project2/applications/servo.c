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
#include "rtthread.h"

void init (void) {
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

    char thread_name = "servo_thread";
    rt_uint32_t thread_stackSize = 32;
    rt_uint8_t thread_priority = 1;
    rt_uint32_t thread_tick = RT_NULL;

    rt_thread_t servo_thread = rt_thread_create(thread_name, servo_send, RT_NULL, thread_stackSize, thread_priority, thread_tick);

    return;

}

void servo_send() {
    return;
}
