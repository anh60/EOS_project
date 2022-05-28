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
#include "cpu.h"

int main(void)
{

    //Objects
    sensor_temp_t sensor_temp_1;
    cpu_t         cpu_usage_1;

    //Initialize objects
    //temperature sensor
    sensor_temp_1 = sensor_temp_init();

    if(!sensor_temp_1) {
        rt_kprintf("Failed to initialize temperature sensor");
        return RT_ERROR;
    }

    //cpu usage
    cpu_usage_1 = cpu_performance_init();
    if(!cpu_usage_1) {
        rt_kprintf("Failed to initialize cpu usage");
        return RT_ERROR;
    }

    //Start threads in objects
    cpu_usage_start(cpu_usage_1);
    sensor_temp_start(sensor_temp_1);


    int count = 1;
    while (count++)
    {
        rt_kprintf("CPU USAGE: %d.%d% \n", cpu_usage_1->major, cpu_usage_1->minor);
        rt_kprintf("ADC TEMP: %d \n", sensor_temp_1->temperature);
        if(sensor_temp_1->flag == 1) rt_kprintf("Temperature is too hot! \n");
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
