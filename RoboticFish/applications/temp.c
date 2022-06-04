#include <rtthread.h>
#include <stdlib.h>
#include <rtdef.h>

#include "temp.h"

struct sensor_temp sensor_temp;


/**
 * @brief Thread generating mock data to simulate readings from a temperature sensor.
 *        Changes the value of the temp value in the sensor_temp object passed into the function.
 *        Temperature values is in the range 0-256.
 *
 * @param param temp_sensor object
 */
static void read_temp(void *param)
{
    /*Read temperature*/
    struct sensor_temp *sensor_temp = param;

    rt_enter_critical();
        sensor_temp->flag = 0;
        //Generate random ADC value from 0 to 2^NBIT
        uint8_t range = 1 << ADC_NBITS;
        uint8_t temp = rand() % range;
        sensor_temp->temperature = temp;

        // Temperature critically high, trigger sensor flag
        if (sensor_temp->temperature > 200) sensor_temp->flag = 1;
    rt_exit_critical();
}


/**
 * @brief Stores temperature registered by the sensor to flash memory section 4 of the mcu.
 *
 * @param param temp_sensor object
 */
static void store_temp(void *param)
{
    /*Store temperature using store_temp*/
    //struct sensor_temp *sensor_temp = param;

    //TODO: STORE TEMP IN MEMORY
    rt_enter_critical();
    /*rt_kprintf("Running store_temp at ticks %d and storing variable %d \n",
                    rt_tick_get(),
                    sensor_temp->temperature
                    ); */

    rt_exit_critical();
}



/**
 * @brief Initializes and starts up timers and threads needed.
 *
 * @return sensor_temp_t
 */
sensor_temp_t sensor_temp_init(void)
{
   /* Initialize sensor variables */
    sensor_temp.temperature          = 0;
    sensor_temp.flag                 = 0;
   /* Initialize base variables */
    sensor_temp.base.active_threads       = 0;
    sensor_temp.base.function_pointers[TOTAL_THREADS-1] = read_temp;
    sensor_temp.base.function_pointers[TOTAL_THREADS-2] = store_temp;
    sensor_temp.base.action_period[TOTAL_THREADS-1]     = READ_TEMP_THREAD_ACTION_PERIOD;
    sensor_temp.base.action_period[TOTAL_THREADS-2]     = STORE_TEMP_THREAD_ACTION_PERIOD;



   /* Initialize thread 1 */
    sensor_temp.base.threads[TOTAL_THREADS-1] = rt_thread_create("read_temp",    //Name
                                              next_periodic_thread,              //Thread
                                              &sensor_temp,                      //Object
                                              READ_TEMP_THREAD_STACK_SIZE,
                                              READ_TEMP_THREAD_PRIORITY,
                                              READ_TEMP_THREAD_TIMESLICE
                                              );

    if(!sensor_temp.base.threads[TOTAL_THREADS-1])
        return RT_NULL;



    /* Initialize thread 2 */
     sensor_temp.base.threads[TOTAL_THREADS-2] = rt_thread_create("store_temp",  //Name
                                               next_periodic_thread,             //Thread
                                               &sensor_temp,                     //Object
                                               STORE_TEMP_THREAD_STACK_SIZE,
                                               STORE_TEMP_THREAD_PRIORITY,
                                               STORE_TEMP_THREAD_TIMESLICE
                                               );

     if(!sensor_temp.base.threads[TOTAL_THREADS-2])
         return RT_NULL;


    return &sensor_temp;
}

/* Start threads */
void sensor_temp_start(void *param)
{
    struct sensor_temp *sensor_temp = param;

    rt_thread_startup(sensor_temp->base.threads[TOTAL_THREADS-1]);
    rt_thread_startup(sensor_temp->base.threads[TOTAL_THREADS-2]);
}

