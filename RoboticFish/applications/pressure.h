/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */
#ifndef APPLICATIONS_PRESSURE_H_
#define APPLICATIONS_PRESSURE_H_

#define RT_TIMER_FLAG_PERIODIC      0x2     /* Periodic timing     */

int pressure_init(void);
static int pressure_get(void);
static void pressure_store(int pressure);
static void pressure_handler(void *param);


#endif /* APPLICATIONS_PRESSURE_H_ */
