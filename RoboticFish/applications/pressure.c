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



struct sensor_pressure sensor_pressure;



/**
 * @brief Mock function to simulate pressure sersor input data.
 *
 * @return int - random integer in the range 0-1024.
 */
static int pressure_get(void)
{
    // Read and return pressure from device
    // Mock function
    uint32_t r = rand() % 1024;

    return r;
}

// TODO how many bits do we need to store possible data values?
/**
 * @brief Function storing pressure data to sector 4 of the microcontroller
 *        flash memory. Remark: if the value is to be read out again the
 *        bits need to be rearranged in the correct edian as usual when working
 *        with flash memory.
 *
 * @param pressure 32 bit integer
 */
static void pressure_store(uint32_t pressure)
{
    
    static int flash_addr = ADDR_FLASH_SECTOR_4;
    
    // Unlock flash memory
    HAL_FLASH_Unlock();

    FLASH_Program_Word(flash_addr, pressure);

    // Lock flash memory
    HAL_FLASH_Lock();


    flash_addr += 16;

    return;
}

/**
 * @brief Thread using functions pressure_get and pressure_store to
 *        read and store pressure sensor data. Triggered periodically in
 *        periods of 75 ms.
 *
 * @param param
 */
static void pressure_handler(void *param)
{
    struct sensor_pressure *sensor_pressure = param;

   sensor_pressure->pressure = pressure_get();
   pressure_store(sensor_pressure->pressure);

   return;
}


/**
 * @brief initialization and startup function for the pressure module.
 *        Activates the timer, event and thread needed. Does some light error detection.
 *
 * @return int
 *          0 - no errors
 *         -1 - event init error
 *         -2 - thread startup error
 *         -3 - timer startup error
 */
sensor_pressure_t sensor_pressure_init(void)
{

    /* Initialize sensor variables */
    sensor_pressure.pressure = 0;
    sensor_pressure.flag     = 0;
    /* Initialize base variables */
    sensor_pressure.base.active_threads                     = 0;
    sensor_pressure.base.function_pointers[TOTAL_THREADS-1] = pressure_handler;
    sensor_pressure.base.action_period[TOTAL_THREADS-1]     = TIMEOUT;



    /* Initialize thread 1 */

    sensor_pressure.base.threads[TOTAL_THREADS-1] = rt_thread_create("pressure_thread",
                                                  next_periodic_thread,
                                                  &sensor_pressure,
                                                  THREAD_STACK_SIZE,
                                                  THREAD_PRIORITY,
                                                  THREAD_TIMESLICE
                                                  );

    if(!sensor_pressure.base.threads[TOTAL_THREADS-1])
        return RT_NULL;

    return &sensor_pressure;
}

/**
 * @brief Function triggered by the correlating timer to send an event to the suspended thread.
 *
 * @param param pressure object.
 */
void sensor_pressure_start(void *param)
{
    struct sensor_pressure *sensor_pressure = param;

    rt_thread_startup(sensor_pressure->base.threads[TOTAL_THREADS-1]);

    return;
}



