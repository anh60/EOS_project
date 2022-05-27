
#ifndef __BASE_H__
#define __BASE_H__

#include <rtdef.h>

//Change if necessary
#define TOTAL_THREADS 5

typedef struct {
    uint8_t active_threads;
    rt_thread_t threads[TOTAL_THREADS];
    /*Functions to execute in periodic thread*/
    void (*function_pointers[TOTAL_THREADS])(void *parameter);
    /*Action period for periodic thread*/
    uint16_t action_period[TOTAL_THREADS];
} base_struct;

#endif /* __BASE_H__ */
