/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */
#ifndef __TEMP_H__
#define __TEMP_H__

#include <rtdef.h>


//READ_TEMP
#define READ_TEMP_STACK_SIZE  1024
#define READ_TEMP_PRIORITY 1
#define READ_TEMP_ACTION_PERIOD 500 /* 5 seconds */
//STORE_TEMP
#define STORE_TEMP_STACK_SIZE 1024
#define STORE_TEMP_PRIORITY 1

struct sensor_temp {
    rt_thread_t read_temp;
    rt_thread_t store_temp;

    int temperature;
};
typedef struct sensor_temp *sensor_temp_t;

//Threads
int read_temp(void *param);
void store_temp(void *param);
//Functions
sensor_temp_t sesnor_temp_init(void *param);

#endif /* __TEMP_H__ */
