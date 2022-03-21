/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */

#include <rtthread.h>
#include "pressure.h"
#include <stdlib.h>
#include "board.h"
#include "stm32f4xx_hal.h"

#define THREAD_PRIORITY         2
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        1
#define TIMEOUT                 2000  //TODO 75 ms
#define EVENT_FLAG3             (1 << 3)
#define MEM_START_ADDR          0x70000000
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */


static rt_thread_t pressure_thread = RT_NULL;
static struct rt_event event;

/* Thread Sample */
int pressure_init(void){

    // EVENT INIT
    rt_err_t err = rt_event_init(&event, "event", RT_IPC_FLAG_FIFO);
    if (err != RT_EOK)
    {
        rt_kprintf("init event failed.\n");
        return -1;
    }

    static rt_timer_t pressure_timer;

    pressure_timer = rt_timer_create("pressure_timer",
                                     start_thread,
                                     RT_NULL,
                                     TIMEOUT,
                                     RT_TIMER_FLAG_PERIODIC);

    // Create thread
    pressure_thread = rt_thread_create("pressure_thread",
                                        pressure_handler,
                                        pressure_thread,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY,
                                        THREAD_TIMESLICE
                                        );

    // Check that creation of thread was successful
    if ( pressure_thread == RT_NULL) { return -1; }
    rt_thread_startup(pressure_thread);

    err = rt_timer_start(pressure_timer);
    if (err != RT_NULL) {return -1;}

    return 0;
}

static int pressure_get(void) {
    // Read and return pressure from device
    // Mock function
    u_int32_t r = rand() % 1024;

    return r;
}

//fair å bare lagre en byte for 254 psi tilsvarer
static void pressure_store(u_int32_t pressure) {
    static int flash_addr = ADDR_FLASH_SECTOR_4;
    // Unlock flash memory
    //pressure = rearrange4mem(pressure);
    HAL_FLASH_Unlock();

    // FLASH_Program_HalfWord(uint32_t Address, uint32_t Data);
    FLASH_Program_Word(flash_addr, pressure);

    // Lock flash memory
    HAL_FLASH_Lock();

    flash_addr += 16;

    return;
}

//TODO check that it is no problem suspending oneself
static void pressure_handler(void *param) {
    rt_uint32_t e;

    while(1){

        rt_kprintf("In pressure handler \n");

        int pressure = pressure_get();
        pressure_store(pressure);
        rt_kprintf("Pressure %d \n", pressure);


        if (rt_event_recv(&event,
                          EVENT_FLAG3,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        { rt_kprintf("Event received pressure thread. \n", e); }

    }

    return;
}

static void start_thread(void *param){

    rt_event_send(&event, EVENT_FLAG3);

    return;
}

static void FLASH_Program_Word(uint32_t Address, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t*)Address = Data;
}

//only needed if we are going to read back
static uint32_t rearrange4mem(uint32_t data){
    uint32_t tmp = data;
    tmp &= 0x11000000;
    tmp = tmp >> 6;

    data &= 0x00110000;
    data = data >> 2;

    data |= tmp;

    return data;
}

