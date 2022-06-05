/**
 * @file pressure.h
 * @author Maja Markusson
 * @brief Functions and objects to calculate and set the position of servo motors given preplanned
 *        positions in degrees. The functionality is implemented using independent threads for the
 *        two tasks.
 * 
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __PRESSURE_H__
#define __PRESSURE_H__

#include "base.h"


#define PRESSURE_HANDLER_THREAD_STACK_SIZE    2048
#define PRESSURE_HANDLER_THREAD_PRIORITY      5
#define PRESSURE_HANDLER_THREAD_TIMESLICE     5
#define PRESSURE_HANDLER_THREAD_ACTION_PERIOD (75 * TICKS_MS)



struct sensor_pressure {
    base_struct base;
    uint32_t pressure;
};
typedef struct sensor_pressure *sensor_pressure_t;

sensor_pressure_t sensor_pressure_init(void);
void sensor_pressure_start(void *param);


#endif /* __PRESSURE_H__ */
