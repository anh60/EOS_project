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
    {return -1; }

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

        rt_kprintf("In set position thread \n");                        //for debugging

        //set set voltage signals based on servo_value array

        if (rt_event_recv(&event,
                          EVENT_FLAG3,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        { rt_kprintf("Event received servo set thread. \n", e); }       //for debugging

    }

    return;
}

static void servo_calculate_positions(void *param) {
    struct servo_motor *servo = param;
    rt_uint32_t e;
    static int array_offset = 0;
    int *servo_value_array = servo->servo_value_array;

    // This is the first delay to synchronize the execution of the two threads
    rt_thread_delay(40 * TICKS_MS);

    // A possibility is to open a file and read from it or can it just be retrived from prog.mem
    // need to produce a PWM signal from degrees to ms

    while(1){

        int servo1 = degToPWM(servo_value_array[array_offset]);
        int servo2 = degToPWM(servo_value_array[array_offset + 1]);
        int servo3 = degToPWM(servo_value_array[array_offset + 2]);

        array_offset = array_offset + 3;

        servo->servo_value[0] = servo1;
        servo->servo_value[1] = servo2;
        servo->servo_value[2] = servo3;

        rt_kprintf("In servo calculation thread \n");                   //for debugging

        if (rt_event_recv(&event,
                          EVENT_FLAG4,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        { rt_kprintf("Event received servo calc. thread. \n", e); }     //for debugging
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

static int degToPWM(int valDeg) {
    //0 = 500 us
    //180 = 2500 us
    // theoretical precision to 0.09

    int pwm = (valDeg / 0.09) + 500;

    return pwm;
}


