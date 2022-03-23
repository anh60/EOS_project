#include <rtthread.h>
#include <stdlib.h>
#include <rtdef.h>

#include "temp.h"

#define EVENT_FLAG1          (1 << 1)
#define EVENT_FLAG2          (1 << 2)

struct sensor_temp sensor_temp;
rt_event_t event;
rt_timer_t timer_read_temp;
rt_timer_t timer_store_temp;


static void timer_trigger_read_temp(void *param){
    /*Trigger thread 1*/
    struct sensor_temp *sensor_temp = param;
    rt_thread_resume(sensor_temp->read_temp);
    rt_schedule();
}

static void timer_trigger_store_temp(void *param){
    /*Trigger thread 2*/
    struct sensor_temp *sensor_temp = param;
    rt_thread_resume(sensor_temp->store_temp);
    rt_schedule();
}

/* Thread 1 */
static void read_temp(void *param)
{
    /*Read temperature*/
    struct sensor_temp *sensor_temp = param;

    while(1)
    {
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

            rt_thread_startup(sensor_temp->extr_temp);

        }

        rt_thread_delay(1000);
    }

}

/* Thread 2 */
static void store_temp(void *param)
{
    /*Store temperature using store_temp*/
    struct sensor_temp *sensor_temp = param;
    rt_uint32_t e;

    while(1)
    {
        rt_enter_critical();
        rt_kprintf("Running store_temp at ticks %d and storing variable %d \n",
                    rt_tick_get(),
                    sensor_temp->temperature);

        rt_exit_critical();

        rt_thread_delay(1000);
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

    // TODO this is needed to initialize events
    // EVENT INIT
    rt_err_t err = rt_event_init(&event, "event", RT_IPC_FLAG_FIFO);
    if (err != RT_EOK)
    {
        rt_kprintf("init event failed.\n");
        return -1;
    }


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

     // Initialize thread extr_temp
     sensor_temp.extr_temp = rt_thread_create("extr_temp",           //Name
                                                handle_extr_temp,            //Function
                                                &sensor_temp,          //Object
                                                EXTR_TEMP_STACK_SIZE, //Stack size
                                                EXTR_TEMP_PRIORITY,   //Priority
                                                1                      //Ticks
                                                );
     if(!sensor_temp.extr_temp)
         return RT_NULL;


     /* Initialize timers */
      timer_read_temp = rt_timer_create("timer_read_temp",
                                         timer_trigger_read_temp, //Use maybe timer trigger instead
                                         &sensor_temp,
                                         READ_TEMP_ACTION_PERIOD,
                                         RT_TIMER_FLAG_PERIODIC
                                         );

      if(!timer_read_temp)
          return RT_NULL;
      rt_timer_start(timer_read_temp);


      timer_store_temp = rt_timer_create("timer_store_temp",
                                          timer_trigger_store_temp,  //Use maybe timer trigger instead
                                          &sensor_temp,
                                          STORE_TEMP_ACTION_PERIOD,
                                          RT_TIMER_FLAG_PERIODIC
                                          );

      if(!timer_store_temp)
          return RT_NULL;
      rt_timer_start(timer_store_temp);



    return &sensor_temp;
}

