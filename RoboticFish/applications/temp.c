#include <rtthread.h>

#include "temp.h"

struct sensor_temp sensor_temp;

/* Thread 1 */
static void read_temp(void *param)
{
    /*Read and return temperature*/
    struct sensor_temp *sensor_temp = param;
    //Generate random ADC value from 0 to 2^NBIT
    int range = 1 << ADC_NBITS;
    int temp = srand(time(0)) % range;

    sensor_temp->temperature = temp;
}

/* Thread 2 */
static void store_temp(void *param)
{
    /*Store temperature using store_temp*/
}

/* Initialize temperature sensor */
sensor_temp_t sensor_temp_init(void)
{
   /* Initialize variables */
    sensor_temp.temperature = 0;

   /* Initialize thread 1 */
  /*  sensor_temp.read_temp = rt_thread_create_periodic("read_temp",              //Name
                                                       read_temp,               //Function
                                                       &sensor_temp,            //Object
                                                       READ_TEMP_STACK_SIZE,    //Stack size
                                                       READ_TEMP_PRIORITY,      //Priority
                                                       1,                       //Ticks
                                                       READ_TEMP_ACTION_PERIOD  //Period
                                                       );

    if(!sensor_temp.read_temp)
        return RT_NULL;

    /* Initialize thread 2 */
     sensor_temp.store_temp = rt_thread_create("store_temp",           //Name
                                                store_temp,            //Function
                                                &sensor_temp,          //Object
                                                STORE_TEMP_STACK_SIZE, //Stack size
                                                STORE_TEMP_PRIORITY,   //Priority
                                                1                      //Ticks
                                                );
     if(!sensor_temp.store_temp)
         return RT_NULL;

    return &sensor_temp;
}

