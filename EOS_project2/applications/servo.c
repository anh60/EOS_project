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
}
