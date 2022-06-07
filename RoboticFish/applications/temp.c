#include <rtthread.h>
#include <stdlib.h>
#include <rtdef.h>

#include "temp.h"
#include "flash.h"


struct sensor_temp sensor_temp;


/**
 * @brief Thread generating mock data to simulate readings from a temperature sensor.
 *        Changes the value of the temp value in the sensor_temp object passed into the function.
 *        Temperature values is in the range 0-256.
 *
 * @param param temp_sensor object
 */
static uint8_t read_temp()
{
    //Generate random ADC value from 0 to 2^NBIT
    int16_t range = 1 << ADC_NBITS;
    uint8_t temp = rand() % range;
    return temp;
}


/**
 * @brief Stores temperature registered by the sensor to flash memory section 4 of the mcu.
 *
 * @param param temp_sensor object
 */
static void store_temp(void *param)
{
    //TODO: STORE TEMP IN MEMORY
    /*Store temperature using store_temp*/
    struct sensor_temp *sensor_temp = param;

    sensor_temp->flag = 0;
    sensor_temp->temperature = read_temp();


    // Temperature critically high, trigger sensor flag
    if (sensor_temp->temperature > 200) sensor_temp->flag = 1;

    static int flash_addr = ADDR_FLASH_SECTOR_4;

    // Unlock flash memory
    rt_enter_critical();
    HAL_FLASH_Unlock();

    FLASH_Program_Word(flash_addr, sensor_temp->temperature);

    // Lock flash memory
    HAL_FLASH_Lock();
    rt_exit_critical();


    flash_addr += 16;

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
    sensor_temp.base.function_pointers[TOTAL_THREADS-1] = store_temp;
    sensor_temp.base.action_period[TOTAL_THREADS-1]     = STORE_TEMP_THREAD_ACTION_PERIOD;



   /* Initialize thread 1 */
     sensor_temp.base.threads[TOTAL_THREADS-1] = rt_thread_create("temp",  //Name
                                               next_periodic_thread,             //Thread
                                               &sensor_temp,                     //Object
                                               STORE_TEMP_THREAD_STACK_SIZE,
                                               STORE_TEMP_THREAD_PRIORITY,
                                               STORE_TEMP_THREAD_TIMESLICE
                                               );

     if(!sensor_temp.base.threads[TOTAL_THREADS-1])
         return RT_NULL;


    return &sensor_temp;
}

/* Start threads */
void sensor_temp_start(void *param)
{
    struct sensor_temp *sensor_temp = param;

    rt_thread_startup(sensor_temp->base.threads[TOTAL_THREADS-1]);
}

void sensor_temp_close(void *param)
{
    struct sensor_temp *sensor_temp = param;

    rt_thread_delete(sensor_temp->base.threads[TOTAL_THREADS-1]);
}

