/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */
#ifndef APPLICATIONS_SERVO_H_
#define APPLICATIONS_SERVO_H_

#define RT_TIMER_FLAG_PERIODIC      0x2     /* Periodic timing     */

void servo_init(void);
static void servo_set_positions(int id, int servo_value);
static int servo_calculate_positions(int servo_value);

#endif /* APPLICATIONS_SERVO_H_ */
