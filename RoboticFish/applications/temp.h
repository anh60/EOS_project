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
#define READ_TEMP_STACK_SIZE    1024
#define READ_TEMP_PRIORITY      2
#define READ_TEMP_ACTION_PERIOD 500     /* 1 seconds = 1000 ticks */
//STORE_TEMP
#define STORE_TEMP_STACK_SIZE    1024
#define STORE_TEMP_PRIORITY      2
#define STORE_TEMP_ACTION_PERIOD 2000   /* 1 seconds = 1000 ticks */


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


//THREADS
/**
 * @brief Thread generating mock data to simulate readings from a temperature sensor. 
 *        Changes the value of the temp value in the sensor_temp object passed into the function. 
 *        Temperature values is in the range 0-256.
 * 
 * @param param temp_sensor object
 */
void read_temp(void *param);

/**
 * @brief Stores temperature registered by the sensor to flash memory section 4 of the mcu. 
 * 
 * @param param temp_sensor object
 */
void store_temp(void *param);

//FUNCTIONS
/**
 * @brief Initializes and starts up timers and threads needed.  
 * 
 * @return sensor_temp_t 
 */
sensor_temp_t sensor_temp_init(void);
void sensor_temp_start(void *param);

#endif /* __TEMP_H__ */
