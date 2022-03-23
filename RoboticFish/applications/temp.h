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


#define ADC_NBITS 8;
//READ_TEMP
#define READ_TEMP_STACK_SIZE  1024
#define READ_TEMP_PRIORITY 1
#define READ_TEMP_ACTION_PERIOD 500     /* 1 seconds = 1000 ticks */
//STORE_TEMP
#define STORE_TEMP_STACK_SIZE 1024
#define STORE_TEMP_PRIORITY 2
#define STORE_TEMP_ACTION_PERIOD 2000   /* 1 seconds = 1000 ticks */
//EXTR_TEMP
#define EXTR_TEMP_STACK_SIZE 1024
#define EXTR_TEMP_PRIORITY 4           //TODO denne må ha høyere prioritet
#define EXTR_TEMP_ACTION_PERIOD 2000   /* 1 seconds = 1000 ticks */



struct sensor_temp {
    rt_thread_t read_temp;
    rt_thread_t store_temp;
    rt_thread_t extr_temp;

    int temperature;
};
typedef struct sensor_temp *sensor_temp_t;


//Timer triggers
static void timer_trigger_read_temp(void *param);
static void timer_trigger_store_temp(void *param);

//Threads
static void read_temp(void *param);
static void store_temp(void *param);
static void handle_extr_temp(void *param);

//Functions
sensor_temp_t sensor_temp_init(void);

#endif /* __TEMP_H__ */
