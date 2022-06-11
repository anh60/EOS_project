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

//STORE_TEMP
#define STORE_TEMP_THREAD_STACK_SIZE    2048
#define STORE_TEMP_THREAD_PRIORITY      4
#define STORE_TEMP_THREAD_TIMESLICE     5
#define STORE_TEMP_THREAD_ACTION_PERIOD (100 * TICKS_MS)   /* 1 seconds = 1000 ticks */

//EXTREME_TEMP_HANDLER
#define EXTREME_TEMP_HANDLER_THREAD_STACK_SIZE    2048
#define EXTREME_TEMP_HANDLER_THREAD_PRIORITY      0
#define EXTREME_TEMP_HANDLER_THREAD_TIMESLICE     5


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
void sensor_temp_close(void *param);

#endif /* __TEMP_H__ */
