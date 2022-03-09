/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */

#include <rtthread.h>
#include <rttime.h>
#include "pressure.h"

#define THREAD_PRIORITY         50
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        RT_NULL

static rt_thread_t pressure_thread = RT_NULL;
static char storePressure_stack[1024];

/* Thread Sample */
int pressure_init(void){

    // Create thread
    pressure_thread = rt_thread_create("pressure_thread",
                                    pressure_handler,
                                    RT_NULL,
                                    THREAD_STACK_SIZE,
                                    THREAD_PRIORITY, THREAD_TIMESLICE);

    // Check that creation of thread was successful
    if ( pressure_thread == RT_NULL) { return -1; }

    //init timers
    static rt_timer_t pressure_timer;

    //this is in clockticks
    //TODO convert into ms
    int timeout_clockticks = 10;

    pressure_timer = rt_timer_create("pressure_timer", servo_calculate_positions,
                                 RT_NULL, timeout_clockticks,
                                 RT_TIMER_FLAG_PERIODIC);

    return 0;
}

static int pressure_get(void) {
     /*Read and return pressure from device*/
    return 0;
}

static void pressure_store(int pressure) {
    // store temp to memory
    return;
}

//TODO check that it is no problem suspending oneself
static void pressure_handler(void) {
    int pressure = pressure_get();
    pressure_store(pressure);

    rt_err_t err = rt_thread_suspend(pressure_thread);

    if (err != RT_EOK) {
        //some error has occurred, fix
    }

    rt_schedule();

    return;
}

//TODO what this function do?:))
/* Export to msh command list */
MSH_CMD_EXPORT(thread_sample, thread sample);
