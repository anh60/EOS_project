#include <rtthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "cpuusage.h"

struct cpu cpu;

/* Thread 1 */
static void cpu_usage(void* param)
{
    struct cpu *cpu = param;

    //FILE *file = fopen("benchmarks.txt", "a");
    //fprintf(file, "%d.%d\n", cpu->major, cpu->minor);
    //fclose(file);


   cpu_usage_get(&cpu->major, &cpu->minor);
   rt_thread_delay(PRINT_CPU_USAGE_ACTION_PERIOD);
}

/* Initialize CPU usage */
cpu_t cpu_performance_init(void)
{
  /* Initialize cpu variables */
    cpu.major = 0;
    cpu.minor = 0;
  /* Initialize base variables */
    cpu.base.active_threads  = 0;
    cpu.base.function_pointers[TOTAL_THREADS-1] = cpu_usage;
    cpu.base.action_period[TOTAL_THREADS-1]     = PRINT_CPU_USAGE_ACTION_PERIOD;


  /* Initialize thread 1 */
    cpu.base.threads[TOTAL_THREADS-1] = rt_thread_create("cpu_usage",           //Name
                                                  next_periodic_thread,         //Thread
                                                  &cpu,                         //Object
                                                  PRINT_CPU_USAGE_STACK_SIZE,   //Stack size
                                                  PRINT_CPU_USAGE_PRIORITY,     //Priority
                                                  1
                                                  );

    if(!cpu.base.threads[TOTAL_THREADS-1])
        return RT_NULL;

   return &cpu;
}

/* Start threads */
void cpu_usage_start(void *param)
{
    struct cpu *cpu = param;

    cpu_usage_init();
    rt_thread_startup(cpu->base.threads[TOTAL_THREADS-1]);
}
