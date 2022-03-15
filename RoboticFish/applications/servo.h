/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */
#include <rtdef.h>

#ifndef APPLICATIONS_SERVO_H_
#define APPLICATIONS_SERVO_H_

#define RT_TIMER_FLAG_PERIODIC      0x2     /* Periodic timing */
#define RT_TIMER_FLAG_ONE_SHOT      0x0     /* One shot timing */

struct servo_motor {
    rt_thread_t servo_thread_calculate;
    rt_thread_t servo_thread_set;

    int servo_value[3];
};

typedef struct servo_motor *servo_motor_p;

int servo_init(void);
static void servo_set_positions(void *param);
static void servo_calculate_positions(void *param);
static void start_thread_set(void *param);
static void start_thread_calculate(void *param);

#endif /* APPLICATIONS_SERVO_H_ */
