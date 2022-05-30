#ifndef __CPU_H__
#define __CPU_H__

#include <rtdef.h>
#include "cpuusage.h"
#include "base.h"



//CPU_USAGE
#define CPU_USAGE_THREAD_STACK_SIZE      1024
#define CPU_USAGE_THREAD_PRIORITY        1
#define CPU_USAGE_THREAD_TIMESLICE       1
#define CPU_USAGE_THREAD_ACTION_PERIOD   (20 * TICKS_MS)  /* 1 seconds = 1000 ticks */



struct cpu {
    base_struct base;
    rt_uint8_t major;
    rt_uint8_t minor;
};
typedef struct cpu *cpu_t;


cpu_t cpu_performance_init(void);
void cpu_usage_start(void *param);

#endif /* __CPU_H__ */
