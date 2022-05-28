
#ifndef __BASE_H__
#define __BASE_H__

#include <rtdef.h>

//Change if necessary
#define TOTAL_THREADS 5

/* IMPORTANT INFORMATION
 *
 * PERIODIC THREADS START FROM TOTAL_THREADS-1, -2, -N
 * ONE SHOT THREADS START FROM 0, 1, 2, N
 *
 * next_periodic_thread WILL NOT WORK IF CONVENTION IS BROKEN
 */
typedef struct {
    uint8_t active_threads;
    rt_thread_t threads[TOTAL_THREADS];
    /*Functions to execute in periodic thread*/
    void (*function_pointers[TOTAL_THREADS])(void *parameter);
    /*Action period for periodic thread*/
    uint16_t action_period[TOTAL_THREADS];
} base_struct;

#endif /* __BASE_H__ */
