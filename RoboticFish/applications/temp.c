#include <rtthread.h>
#include <stdlib.h>
#include <rtdef.h>

#include "temp.h"

struct sensor_temp sensor_temp;


/* Thread 1 */
static void read_temp(void *param)
{
    /*Read temperature*/
    struct sensor_temp *sensor_temp = param;

    //Do periodic thread
    //while(1)
    //{
        rt_enter_critical();
        sensor_temp->flag = 0;
        //Generate random ADC value from 0 to 2^NBIT
        int range = 1 << ADC_NBITS;
        int temp = rand() % range;
        sensor_temp->temperature = temp;

        rt_kprintf("Running read_temp at ticks %d and reading variable %d \n",
                    rt_tick_get(),
                    sensor_temp->temperature
                    );
        rt_exit_critical();


        // Temperature critically high, trigger sensor flag
        if (sensor_temp->temperature > 200) sensor_temp->flag = 1;

        //rt_thread_delay(READ_TEMP_ACTION_PERIOD);
    //}
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
                    sensor_temp->temperature
                    );

        rt_exit_critical();

        rt_thread_delay(STORE_TEMP_ACTION_PERIOD);
    }
}


/* Initialize temperature sensor */
sensor_temp_t sensor_temp_init(void)
{
   /* Initialize struct variables */
    sensor_temp.type                 = SENSOR_TEMP;
    sensor_temp.temperature          = 0;
    sensor_temp.active_threads       = 0;
   /* Initialize thread variables */
    sensor_temp.function_pointers[TOTAL_THREADS-1] = read_temp;
    sensor_temp.function_pointers[TOTAL_THREADS-2] = store_temp;
    sensor_temp.action_period[TOTAL_THREADS-1]     = READ_TEMP_ACTION_PERIOD;
    sensor_temp.action_period[TOTAL_THREADS-2]     = STORE_TEMP_ACTION_PERIOD;



   /* Initialize thread 1 */
    sensor_temp.threads[TOTAL_THREADS-1] = rt_thread_create("read_temp",              //Name
                                              nextPeriodicThread,               //Function (Want to pass (void *param, rt_thread_t thread, int ACTION_PERIOD), how??
                                              &sensor_temp,            //Object
                                              READ_TEMP_STACK_SIZE,    //Stack size
                                              READ_TEMP_PRIORITY,      //Priority
                                              1
                                              );

    if(!sensor_temp.threads[TOTAL_THREADS-1])
        return RT_NULL;



    /* Initialize thread 2 */
     sensor_temp.threads[TOTAL_THREADS-2] = rt_thread_create("store_temp",              //Name
                                               nextPeriodicThread,               //Function (Want to pass (void *param, rt_thread_t thread, int ACTION_PERIOD), how??
                                               &sensor_temp,            //Object
                                               STORE_TEMP_STACK_SIZE,    //Stack size
                                               STORE_TEMP_PRIORITY,      //Priority
                                               1
                                               );

     if(!sensor_temp.threads[TOTAL_THREADS-2])
         return RT_NULL;


    return &sensor_temp;
}

/* Start threads */
void sensor_temp_start(void *param)
{
    struct sensor_temp *sensor_temp = param;

    rt_thread_startup(sensor_temp->threads[TOTAL_THREADS-1]);
    rt_thread_startup(sensor_temp->threads[TOTAL_THREADS-2]);

    //Comment out the while loop and delay inside the thread to use this function
    //will currently block everything
    //This function should be the thread passed when creating a thread
     // rt_thread_startup_periodic(sensor_temp);

}

