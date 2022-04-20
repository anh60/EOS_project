/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-04     Maja Markusson       the first version
 */

#include "servo.h"
#include <rtthread.h>
#include "drv_common.h"

#define THREAD_PRIORITY         3
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        1

#define TICKS_MS                10
#define TIMEOUT_SET             (10 * TICKS_MS)
#define TIMEOUT_CALCULATE       (40 * TICKS_MS)

#define EVENT_FLAG3 (1 << 3)
#define EVENT_FLAG4 (1 << 4)

static struct rt_event event;
struct servo_motor servo;

int servo_init (void) {
    
    // EVENT HANDLING
    rt_err_t err = rt_event_init(&event, "event", RT_IPC_FLAG_FIFO);
    if (err != RT_EOK)
    {
        rt_kprintf("init event failed.\n");
        return -1;
    }

    // TIMER HANDLING
    rt_timer_t servo_timer_set = rt_timer_create("servo_timer_set",
                                      start_thread_set,
                                      RT_NULL,
                                      TIMEOUT_SET,
                                      RT_TIMER_FLAG_PERIODIC);


    rt_timer_t servo_timer_calculate = rt_timer_create("servo_timer_calculate",
                                            start_thread_calculate,
                                            RT_NULL,
                                            TIMEOUT_CALCULATE,
                                            RT_TIMER_FLAG_PERIODIC);

    
    // THREAD HANDLING
    servo.servo_thread_set = rt_thread_create("servo_thread_set",
                                        servo_set_positions,
                                        &servo,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY,
                                        THREAD_TIMESLICE);

    servo.servo_thread_calculate = rt_thread_create("servo_thread_calculate",
                                               servo_calculate_positions,
                                               &servo,
                                               THREAD_STACK_SIZE,
                                               THREAD_PRIORITY,
                                               THREAD_TIMESLICE);


    
    // ERROR HANDLING 
    if (servo.servo_thread_set == RT_NULL) { return -2; }
    
    if (servo.servo_thread_calculate == RT_NULL) { return -2; }

    err = rt_thread_startup(servo.servo_thread_set);
    if (err != 0){ return -3;}

    err = rt_thread_startup(servo.servo_thread_calculate);
    if (err != 0){ return -3;}

    err = rt_timer_start(servo_timer_calculate);
    if (err != 0){ return -1;}

    err = rt_timer_start(servo_timer_set);
    if (err != 0){ return -1; }

    return 0;

}

static void servo_set_positions(void *param) {

    // TODO find error handling if no new input has been given 

    rt_uint32_t e;

    while(1){

        rt_kprintf("In set position thread \n");

        if (rt_event_recv(&event,
                          EVENT_FLAG3,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        { rt_kprintf("Event received servo set thread. \n", e); }

    }

    return;
}

static void servo_calculate_positions(void *param) {
    struct servo_motor *servo = param;
    rt_uint32_t e;

    //this is the first delay to synchronize the execution of the two threads
    rt_thread_delay(40 * TICKS_MS);

    while(1){

        servo->servo_value[0] = 0;
        servo->servo_value[1] = 1;
        servo->servo_value[2] = 2;

        rt_kprintf("In servo calculation thread \n");

        if (rt_event_recv(&event,
                          EVENT_FLAG4,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        { rt_kprintf("Event received servo calc. thread. \n", e); }
    }
}

static void start_thread_set(void *param){
    rt_event_send(&event, EVENT_FLAG3);
    return;
}

static void start_thread_calculate(void *param){
    rt_event_send(&event, EVENT_FLAG4);
    return;
}


