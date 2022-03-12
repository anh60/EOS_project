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

int main(void)
{
    //Objects
    sensor_temp_t sensor_temp_1;

    //Initialize temperature sensor
    sensor_temp_1 = sensor_temp_init();

    if(!sensor_temp_1) {
        rt_kprintf("Failed to initialize temperature sensor");
        return RT_ERROR;
    }

    int count = 1;
    while (count++)
    {
        rt_kprintf("ADC TEMP: %d \n", sensor_temp_1->temperature);
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
