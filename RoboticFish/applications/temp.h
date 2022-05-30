/**
 * @file temp.h
 * @author Marcus Alexander Tjomsaas
 * @brief Temperature sensor readings and storage as well as error handling for 
 *        extreme temperatures.
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TEMP_H__
#define __TEMP_H__

#include <rtdef.h>
#include "base.h"

//READ_TEMP
#define ADC_NBITS 8
#define READ_TEMP_THREAD_STACK_SIZE    1024
#define READ_TEMP_THREAD_PRIORITY      2
#define READ_TEMP_THREAD_TIMESLICE     1
#define READ_TEMP_THREAD_ACTION_PERIOD (100 * TICKS_MS)     /* 1 seconds = 1000 ticks */
//STORE_TEMP
#define STORE_TEMP_THREAD_STACK_SIZE    1024
#define STORE_TEMP_THREAD_PRIORITY      5
#define STORE_TEMP_THREAD_TIMESLICE     1
#define STORE_TEMP_THREAD_ACTION_PERIOD (100 * TICKS_MS)   /* 1 seconds = 1000 ticks */


/**
 * @brief Object containing independent threads and the temperature variable
 *        to be passed between them. 
 */

struct sensor_temp {
    base_struct base;
    uint8_t temperature;
    uint8_t flag;
    /* FLAGS:
     * BITS |DESCRIPTION
     * 1    |Triggered when temperature is dangerously hot
     * 2    |Undefined
     * 3    |Undefined
     * 4    |Undefined
     * 5    |Undefined
     * 6    |Undefined
     * 7    |Undefined
     * 8    |Undefined
     */

};
typedef struct sensor_temp *sensor_temp_t;



sensor_temp_t sensor_temp_init(void);
void sensor_temp_start(void *param);

#endif /* __TEMP_H__ */
