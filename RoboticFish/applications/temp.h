/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */
#ifndef __APPLICATIONS_TEMP_H__
#define __APPLICATIONS_TEMP_H__

#define TEMP_THREAD_STACH_SIZE  1024
#define TEMP_HOST_ACTION_PERIOD 500 /* 5 seconds */
#define READ_TEMP_PRIORITY 1
#define STORE_TEMP_PRIORITY 1

struct sensor_temp {
    rt_thread_t read_temp;
    rt_thread_t store_temp;
};
typedef struct sensor_temp *sensor_temp_t;

#endif /* APPLICATIONS_TEMP_H_ */
