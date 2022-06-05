/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-09     RT-Thread    first version
 *
 * PRINT WORKS WITH DEBUG LAUNCH (ctrl + f5)
 */

#include "servo.h"
#include "temp.h"
#include "pressure.h"
#include "cpu.h"

//Objects
servo_motor_t       servo_motors;
sensor_temp_t       sensor_temp_1;
sensor_pressure_t   sensor_pressure_1;
cpu_t               cpu_usage_1;


/* Initialize objects */
int init_threads(void)
{
    //servo
    servo_motors = servo_init();
    if(!servo_motors) {
        rt_kprintf("Failed to initialize servo motors");
        return RT_ERROR;
    }

    //temperature sensor
    sensor_temp_1 = sensor_temp_init();
    if(!sensor_temp_1) {
        rt_kprintf("Failed to initialize temperature sensor");
        return RT_ERROR;
    }

    //pressure sensor
    sensor_pressure_1 = sensor_pressure_init();
    if(!sensor_pressure_1) {
        rt_kprintf("Failed to initialize pressure sensor");
        return RT_ERROR;
    }

    //cpu usage
    cpu_usage_1 = cpu_performance_init();
    if(!cpu_usage_1) {
        rt_kprintf("Failed to initialize cpu usage");
        return RT_ERROR;
    }

    return 0;
}

void start_threads(void)
{
    //Start threads in objects
    servo_start(servo_motors);
    cpu_usage_start(cpu_usage_1);
    sensor_temp_start(sensor_temp_1);
    sensor_pressure_start(sensor_pressure_1);
}

int main(void)
{
    init_threads();
    start_threads();

    while(1)
    {
    }

    /*
    int current_time = 0;
    const int target_time = 20000;
    while(current_time < target_time)
    {
        current_time = rt_tick_get();
        rt_kprintf("T: %d;    \n", current_time);
        rt_kprintf("CPU: %d.%d%; S: %d; E: %d;      ",        cpu_usage_1->major, cpu_usage_1->minor, cpu_usage_1->base.start_tick[TOTAL_THREADS-1], cpu_usage_1->base.end_tick[TOTAL_THREADS-1]);
        rt_kprintf("TEMP: %d; %d; S: %d; E: %d;    ",           sensor_temp_1->flag, sensor_temp_1->temperature, sensor_temp_1->base.start_tick[TOTAL_THREADS-1], sensor_temp_1->base.end_tick[TOTAL_THREADS-1]);
        rt_kprintf("POS: %d ; %d ; %d; S_s: %d; E_s: %d; S_c: %d; E_c: %d;    ",    servo_motors->servo_value_pwm[0], servo_motors->servo_value_pwm[1], servo_motors->servo_value_pwm[2], servo_motors->base.start_tick[TOTAL_THREADS-1], servo_motors->base.end_tick[TOTAL_THREADS-1], servo_motors->base.start_tick[TOTAL_THREADS-2], servo_motors->base.end_tick[TOTAL_THREADS-2]);
        rt_kprintf("PRESS: %d; S: %d; E: %d;   ",                sensor_pressure_1->pressure, sensor_pressure_1->base.start_tick[TOTAL_THREADS-1], sensor_pressure_1->base.end_tick[TOTAL_THREADS-1]);

        rt_kprintf("\n");

        rt_thread_mdelay(20);
    } */
    return RT_EOK;
}
