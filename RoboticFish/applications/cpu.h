#ifndef __CPU_H__
#define __CPU_H__

#include <rtdef.h>
#include "cpuusage.h"

rt_thread_t init_cpu_usage_thread(rt_thread_t thread);
void start_cpu_usage_thread(rt_thread_t thread);

#endif
