#include <rtthread.h>

#include "temp.h"

struct sensor_temp sensor_temp = { };

/* Entry Function for Thread 1 */
static int read_temp(void *parameter)
{
     /*Read and return temperature*/
    return 0;
}

/* Entry for Thread 2 */
//static void store_temp(void *param)
//{
    /*Store temperature using store_temp*/

//}

/* Thread Sample */
int thread_sample(void)
{
   /* Create thread 1, Name is thread1,Entry is thread1_entry */
    sensor_temp.read_temp = rt_thread_create_periodic("read_temp",              //Name
                                                       read_temp,               //Function
                                                       &sensor_temp,            //Stack size; MIGHT NEED TEMP_THREAD_STACH_SIZE INSTEAD
                                                       READ_TEMP_PRIORITY,      //Priority
                                                       1,                       //Ticks
                                                       TEMP_HOST_ACTION_PERIOD  //Period
                                                       );

    /* Start this thread if you get the thread control block */
//    if (tid1 != RT_NULL)
//        rt_thread_startup(tid1);
    return 0;
}

/* Export to msh command list */
//MSH_CMD_EXPORT(thread_sample, thread sample);

