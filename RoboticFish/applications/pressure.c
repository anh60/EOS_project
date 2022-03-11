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

#define THREAD_PRIORITY         50
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        1
#define HOST_ACTION_PERIOD      40

static rt_thread_t pressure_thread = RT_NULL;
static char storePressure_stack[1024];

/* Thread Sample */
int pressure_init(void){

    // Create thread
    pressure_thread = rt_thread_create_periodic("pressure_thread",
                                                pressure_handler,
                                                RT_NULL,
                                                THREAD_STACK_SIZE,
                                                THREAD_PRIORITY,
                                                THREAD_TIMESLICE,
                                                HOST_ACTION_PERIOD
                                                );


    // Check that creation of thread was successful
    if ( pressure_thread == RT_NULL) { return -1; }

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


//map timer til event
