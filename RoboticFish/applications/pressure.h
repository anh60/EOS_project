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
#ifndef APPLICATIONS_PRESSURE_H_
#define APPLICATIONS_PRESSURE_H_

#include "base.h"

struct sensor_pressure {
    base_struct base;
    uint32_t pressure;
    uint8_t flag;
    /* FLAGS:
     * BITS |DESCRIPTION
     * 1    |Triggered when pressure is dangerously high
     * 2    |Undefined
     * 3    |Undefined
     * 4    |Undefined
     * 5    |Undefined
     * 6    |Undefined
     * 7    |Undefined
     * 8    |Undefined
     */

};
typedef struct sensor_pressure *sensor_pressure_t;

sensor_pressure_t sensor_pressure_init(void);
void sensor_pressure_start(void *param);


#endif /* APPLICATIONS_PRESSURE_H_ */
