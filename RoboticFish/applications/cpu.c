#include <rtthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "cpuusage.h"

static void get_cpu_usage(void* param){
    rt_uint8_t major;
    rt_uint8_t minor;
    cpu_usage_get(&major,&minor);
    rt_kprintf("cpu usage = %d.%d%\n",major,minor);
}

rt_thread_t init_cpu_usage_thread(rt_thread_t thread){
    thread = rt_thread_create("cpu_usage",                  //Name
                              get_cpu_usage,                //Function
                              RT_NULL,                      //Object
                              1024,                         //Stack size
                              1,                            //Priority
                              1);                           //Ticks
    return thread;
}

void start_cpu_usage_thread(rt_thread_t thread){
    cpu_usage_init();
    rt_thread_startup(thread);
}
