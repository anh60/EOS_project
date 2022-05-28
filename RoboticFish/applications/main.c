/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-09     RT-Thread    first version
 *
 * PRINT WORKS WITH DEBUG LAUNCH (ctrl + f5)
 */

#include "temp.h"
#include "pressure.h"
#include "cpu.h"

//Objects
sensor_temp_t       sensor_temp_1;
sensor_pressure_t   sensor_pressure_1;
cpu_t               cpu_usage_1;


/* Initialize objects */
int init_threads()
{
    //temperature sensor
    sensor_temp_1 = sensor_temp_init();
    if(!sensor_temp_1) {
        rt_kprintf("Failed to initialize temperature sensor");
        return RT_ERROR;
    }

    //pressure sensor
    sensor_pressure_1 = sensor_pressure_init();
    if(!sensor_pressure_1) {
        rt_kprintf("Failed to initialize pressure sensor");
        return RT_ERROR;
    }

    //cpu usage
    cpu_usage_1 = cpu_performance_init();
    if(!cpu_usage_1) {
        rt_kprintf("Failed to initialize cpu usage");
        return RT_ERROR;
    }

    return 0;
}

void start_threads()
{
    //Start threads in objects
    cpu_usage_start(cpu_usage_1);
    sensor_temp_start(sensor_temp_1);
    sensor_pressure_start(sensor_pressure_1);
}

int main(void)
{
    init_threads();
    start_threads();


    int count = 1;
    while (count++)
    {
        rt_kprintf("CPU USAGE: %d.%d%;      ", cpu_usage_1->major, cpu_usage_1->minor);
        rt_kprintf("ADC TEMP: %d;    ", sensor_temp_1->temperature);
        rt_kprintf("PRESSURE: %d; \n", sensor_pressure_1->pressure);
        if(sensor_temp_1->flag == 1) rt_kprintf("Temperature is too hot! \n");
        rt_thread_mdelay(100);
    }

    return RT_EOK;
}
