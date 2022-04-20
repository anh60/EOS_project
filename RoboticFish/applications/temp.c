#include <rtthread.h>
#include <stdlib.h>
#include <rtdef.h>

#include "temp.h"

struct sensor_temp sensor_temp;


/* Thread 1 */
static void read_temp(void *param){
    /*Read temperature*/
    struct sensor_temp *sensor_temp = param;

    rt_enter_critical();
    //Generate random ADC value from 0 to 2^NBIT
    int range = 1 << ADC_NBITS;
    int temp = rand() % range;
    sensor_temp->temperature = temp;

    rt_kprintf("Running read_temp at ticks %d and reading variable %d \n",
                      rt_tick_get(),
                      sensor_temp->temperature
                      );
    rt_exit_critical();


    // Temperature critically high, launch error handling
    if (sensor_temp->temperature > 200) {

    //rt_thread_startup(sensor_temp->extr_temp);
    }
}


/* Thread 2 */
static void store_temp(void *param)
{
    /*Store temperature using store_temp*/
    struct sensor_temp *sensor_temp = param;

    while(1)
    {
        rt_enter_critical();
        rt_kprintf("Running store_temp at ticks %d and storing variable %d \n",
                    rt_tick_get(),
                    sensor_temp->temperature);

        rt_exit_critical();

        rt_thread_delay(STORE_TEMP_ACTION_PERIOD);
    }
}

static void handle_extr_temp(void *param) {

    rt_kprintf("Temperature too high! \n");

    //TODO delay to cool down or block cpu from doing anything?
    rt_thread_delay(1000);

}

/* Initialize temperature sensor */
sensor_temp_t sensor_temp_init(void)
{
   /* Initialize variable */
    sensor_temp.temperature = 0;


   /* Initialize thread 1 */
    sensor_temp.read_temp = rt_thread_create("read_temp",              //Name
                                              read_temp,               //Function
                                              &sensor_temp,            //Object
                                              READ_TEMP_STACK_SIZE,    //Stack size
                                              READ_TEMP_PRIORITY,      //Priority
                                              1
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


     /* Initialize thread extr_temp
     sensor_temp.extr_temp = rt_thread_create("extr_temp",           //Name
                                                handle_extr_temp,            //Function
                                                &sensor_temp,          //Object
                                                EXTR_TEMP_STACK_SIZE, //Stack size
                                                EXTR_TEMP_PRIORITY,   //Priority
                                                1                      //Ticks
                                                );
     if(!sensor_temp.extr_temp)
         return RT_NULL;
     rt_thread_startup(sensor_temp.extr_temp);*/


    return &sensor_temp;
}

void sensor_temp_start(void *param)
{
    struct sensor_temp *sensor_temp = param;

    rt_thread_startup(sensor_temp->store_temp);
    rt_thread_startup(sensor_temp->read_temp);

    set_thread_periodic(&sensor_temp,           //Object
                        sensor_temp->read_temp,  //Thread
                        READ_TEMP_ACTION_PERIOD //Repeat period
                        );

}

