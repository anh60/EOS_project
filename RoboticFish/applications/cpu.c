#include <rtthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "cpuusage.h"

struct cpu cpu;

/* Thread 1 */
static void print_cpu_usage(void* param)
{
    struct cpu *cpu = param;

    //Test
    cpu->major = 3;
    cpu->minor = 1;
    rt_kprintf("cpu usage = %d.%d%\n",cpu->major,cpu->minor);
    //Test end

    while(1)
    {
        cpu_usage_get(&cpu->major, &cpu->minor);
        rt_kprintf("cpu usage = %d.%d%\n",cpu->major,cpu->minor);
        rt_thread_delay(PRINT_CPU_USAGE_ACTION_PERIOD);

    }
}

/* Initialize CPU usage */
cpu_t cpu_performance_init(void)
{
   cpu.print_cpu_usage = rt_thread_create("cpu_usage",                  //Name
                                          print_cpu_usage,                //Function
                                          &cpu,                      //Object
                                          PRINT_CPU_USAGE_STACK_SIZE,   //Stack size
                                          PRINT_CPU_USAGE_PRIORITY,     //Priority
                                          1                             //Ticks
                                          );

   if(!cpu.print_cpu_usage)
           return RT_NULL;

   return &cpu;
}

/* Start threads */
void cpu_usage_start(void *param)
{
    struct cpu *cpu = param;

    rt_thread_startup(cpu->print_cpu_usage);
}
