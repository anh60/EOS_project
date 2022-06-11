
#ifndef __BASE_H__
#define __BASE_H__

#include <rtdef.h>

/* 1 seconds = 1000 ticks */
#define TICKS_MS 1

//Change if necessary
#define TOTAL_THREADS 5

/* IMPORTANT INFORMATION
 *
 * PERIODIC THREADS START FROM TOTAL_THREADS-1, -2, -N
 * APERIODIC THREADS START FROM 0, 1, 2, TOTAL_THREADS-1
 *
 * next_periodic_thread WILL NOT WORK IF CONVENTION IS BROKEN
 */
typedef struct {
    uint8_t active_periodic_threads;
    rt_thread_t threads[TOTAL_THREADS];
    /*Functions to execute in periodic thread*/
    void (*function_pointers[TOTAL_THREADS])(void *parameter);
    /*Action period for periodic thread*/
    uint16_t action_period[TOTAL_THREADS];


    int offset[TOTAL_THREADS];
    int start_tick[TOTAL_THREADS];
    int end_tick[TOTAL_THREADS];
    int sleep_duration[TOTAL_THREADS];
} base_struct;

#endif /* __BASE_H__ */
