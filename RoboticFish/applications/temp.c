#include <rtthread.h>
#include <stdlib.h>
#include <rtdef.h>

#include "temp.h"

struct sensor_temp sensor_temp;
rt_timer_t timer_read_temp;
rt_timer_t timer_store_temp;


static void timer_trigger_read_temp(void *param){
    /*Trigger thread 1*/
    struct sensor_temp *sensor_temp = param;
    rt_thread_resume(sensor_temp->read_temp);

}

static void timer_trigger_store_temp(void *param){
    /*Trigger thread 2*/
    struct sensor_temp *sensor_temp = param;
    rt_thread_resume(sensor_temp->store_temp);
}

/* Thread 1 */
static void read_temp(void *param)
{
    /*Read and return temperature*/
    struct sensor_temp *sensor_temp = param;

    //Generate random ADC value from 0 to 2^NBIT
    int range = 1 << ADC_NBITS;
    int temp = rand() % range;

    sensor_temp->temperature = temp;
    rt_kprintf("Running read_temp at ticks %d and reading variable %d \n", rt_tick_get(), sensor_temp->temperature);

    //rt_thread_yield();
    //rt_schedule();

}

/* Thread 2 */
static void store_temp(void *param)
{
    /*Store temperature using store_temp*/
    struct sensor_temp *sensor_temp = param;
    rt_kprintf("Running store_temp at ticks %d and storing variable %d \n", rt_tick_get(), sensor_temp->temperature);

    //rt_thread_suspend();
    //rt_schedule();
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
                                              1                        //Ticks
                                              );

    if(!sensor_temp.read_temp)
        return RT_NULL;
    rt_thread_startup(sensor_temp.read_temp);

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
     rt_thread_startup(sensor_temp.store_temp);


     /* Initialize timers */
      timer_read_temp = rt_timer_create("timer_read_temp",
                                         read_temp, //Use maybe timer trigger instead
                                         &sensor_temp,
                                         READ_TEMP_ACTION_PERIOD,
                                         RT_TIMER_FLAG_PERIODIC
                                         );

      if(!timer_read_temp)
          return RT_NULL;
      rt_timer_start(timer_read_temp);


      timer_store_temp = rt_timer_create("timer_store_temp",
                                          store_temp,  //Use maybe timer trigger instead
                                          &sensor_temp,
                                          READ_TEMP_ACTION_PERIOD,
                                          RT_TIMER_FLAG_PERIODIC
                                          );

      if(!timer_store_temp)
          return RT_NULL;
      rt_timer_start(timer_store_temp);

    return &sensor_temp;
}

