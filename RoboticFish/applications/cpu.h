#ifndef __CPU_H__
#define __CPU_H__

#include <rtdef.h>
#include "cpuusage.h"

//CPU_USAGE
#define PRINT_CPU_USAGE_STACK_SIZE      1024
#define PRINT_CPU_USAGE_PRIORITY        1
#define PRINT_CPU_USAGE_ACTION_PERIOD   100  /* 1 seconds = 1000 ticks */

struct cpu {
    rt_thread_t print_cpu_usage;

    rt_uint8_t major;
    rt_uint8_t minor;
};
typedef struct cpu *cpu_t;

//THREADS
cpu_t cpu_performance_init(void);

//FUNCTIONS
void cpu_usage_start(void *param);

#endif /* __CPU_H__ */
