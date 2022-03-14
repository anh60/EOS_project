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
#include "pressure.h"
#include <stdlib.h>

#define THREAD_PRIORITY         2
#define THREAD_STACK_SIZE       256
#define THREAD_TIMESLICE        1
#define TIMEOUT                 10

static rt_thread_t pressure_thread = RT_NULL;

/* Thread Sample */
int pressure_init(void){

    static rt_timer_t pressure_timer;

    pressure_timer = rt_timer_create("pressure_timer",
                                     start_thread,
                                     RT_NULL,
                                     TIMEOUT,
                                     RT_TIMER_FLAG_PERIODIC);

    // Create thread
    pressure_thread = rt_thread_create("pressure_thread",
                                        pressure_handler,
                                        RT_NULL,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY,
                                        THREAD_TIMESLICE
                                        );


    // Check that creation of thread was successful
    if ( pressure_thread == RT_NULL) { return -1; }

    rt_err_t err = rt_timer_start(pressure_timer);
    if (err != RT_NULL) {return -1;}

    return 0;
}

static int pressure_get(void) {
    // Read and return pressure from device
    // Mock function
    int r = rand() % 255;

    return r;
}

static void pressure_store(int pressure) {
    // store temp to memory
    return;
}

//TODO check that it is no problem suspending oneself
static void pressure_handler(void *param) {
    int pressure = pressure_get();
    pressure_store(pressure);

    rt_err_t err = rt_thread_suspend(pressure_thread);

    if (err != RT_EOK) {
        //some error has occurred, fix
    }

    rt_schedule();

    return;
}

static void start_thread(void *param){
    rt_kprintf("start_thread");
    rt_err_t err = rt_thread_startup(pressure_thread);
    if (err != 0){rt_kprintf("mistake");}
    return;
}

