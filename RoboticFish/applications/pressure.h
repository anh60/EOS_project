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

#define RT_TIMER_FLAG_PERIODIC      0x2     /* Periodic timing     */


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



/**
 * @brief initialization and startup function for the pressure module.
 *        Activates the timer, event and thread needed. Does some light error detection.
 * 
 * @return int
 *          0 - no errors
 *         -1 - event init error 
 *         -2 - thread startup error 
 *         -3 - timer startup error
 */
sensor_pressure_t sensor_pressure_init(void);

/**
 * @brief Mock function to simulate pressure sersor input data. 
 * 
 * @return int - random integer in the range 0-1024.
 */
static int pressure_get(void);

/**
 * @brief Function storing pressure data to sector 4 of the microcontroller
 *        flash memory. Remark: if the value is to be read out again the 
 *        bits need to be rearranged in the correct edian as usual when working 
 *        with flash memory. 
 * 
 * @param pressure 32 bit integer
 */
static void pressure_store(uint32_t pressure);

/**
 * @brief Thread using functions pressure_get and pressure_store to
 *        read and store pressure sensor data. Triggered periodically in 
 *        periods of 75 ms. 
 * 
 * @param param 
 */
static void pressure_handler(void *param);

/**
 * @brief Function triggered by the correlating timer to send an event to the suspended thread. 
 * 
 * @param param pressure object. 
 */
void sensor_pressure_start(void *param);



#endif /* APPLICATIONS_PRESSURE_H_ */
