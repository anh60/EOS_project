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
#include "flash.h"

#define THREAD_PRIORITY         2
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        1

#define TICKS_MS                10
#define TIMEOUT                 (75 * TICKS_MS)

#define EVENT_FLAG3             (1 << 3)


static rt_thread_t pressure_thread = RT_NULL;
static struct rt_event event;

/* Thread Sample */
int pressure_init(void){

    // EVENT INIT
    rt_err_t err = rt_event_init(&event, "event", RT_IPC_FLAG_FIFO);

    static rt_timer_t pressure_timer;

    // TIMER INIT
    pressure_timer = rt_timer_create("pressure_timer",
                                     start_thread,
                                     RT_NULL,
                                     TIMEOUT,
                                     RT_TIMER_FLAG_PERIODIC);

    // THREAD INIT
    pressure_thread = rt_thread_create("pressure_thread",
                                        pressure_handler,
                                        pressure_thread,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY,
                                        THREAD_TIMESLICE
                                        );

    
    // ERROR CHECKS
    if (err != RT_EOK){ return -1; }

    if ( pressure_thread == RT_NULL) { return -2; }
    rt_thread_startup(pressure_thread);

    err = rt_timer_start(pressure_timer);
    if (err != RT_NULL) {return -3;}

    return 0;
}

static int pressure_get(void) {
    // Read and return pressure from device
    // Mock function
    uint32_t r = rand() % 1024;

    return r;
}

// TODO how many bits do we need to store possible data values?
static void pressure_store(u_int32_t pressure) {
    
    static int flash_addr = ADDR_FLASH_SECTOR_4;
    
    // Unlock flash memory
    HAL_FLASH_Unlock();

    FLASH_Program_Word(flash_addr, pressure);

    // Lock flash memory
    HAL_FLASH_Lock();

    // 
    flash_addr += 16;

    return;
}

static void pressure_handler(void *param) {
    rt_uint32_t e;

    while(1){

        rt_kprintf("In pressure handler \n");

        int pressure = pressure_get();
        pressure_store(pressure);
        rt_kprintf("Pressure %d \n", pressure);


        if (rt_event_recv(&event,
                          EVENT_FLAG3,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        { rt_kprintf("Event received pressure thread. \n", e); }

    }

    return;
}

static void start_thread(void *param){

    rt_event_send(&event, EVENT_FLAG3);

    return;
}



