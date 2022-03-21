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
static void pressure_store(u_int32_t pressure);
static void pressure_handler(void *param);
static void start_thread(void *param);
static void FLASH_Program_Word(uint32_t Address, uint32_t Data);
static uint32_t rearrange4mem(uint32_t data);


#endif /* APPLICATIONS_PRESSURE_H_ */
