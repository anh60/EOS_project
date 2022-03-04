#include <rtthread.h>

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static rt_thread_t tid1 = RT_NULL;

/* Entry Function for Thread 1 */
static int getTemp(void *parameter)
{
     /*Read and return temperature*/
    return 0;
}

ALIGN(RT_ALIGN_SIZE)
static char storeTemp_stack[1024];
static struct rt_thread storeTemp;


/* Entry for Thread 2 */
static void storeTemp(void *param)
{
    /*Store temperature using getTemp*/

}

/* Thread Sample */
int thread_sample(void)
{
    /* Create thread 1, Name is thread1,Entry is thread1_entry */
    tid1 = rt_thread_create("getTemp",
                            getTemp_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    /* Start this thread if you get the thread control block */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* Create thread 2, Name is thread2, Entry is thread2_entry */
    rt_thread_init(&storeTemp,
                   "storeTemp",
                   storeTemp_entry,
                   RT_NULL,
                   &storeTemp_stack[0],
                   sizeof(storeTemp_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&storeTemp);

    return 0;
}

/* Export to msh command list */
MSH_CMD_EXPORT(thread_sample, thread sample);
