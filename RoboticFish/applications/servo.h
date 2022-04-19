/**
 * @file servo.h
 * @author Maja Markusson
 * @brief 
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <rtdef.h>

#ifndef APPLICATIONS_SERVO_H_
#define APPLICATIONS_SERVO_H_

#define RT_TIMER_FLAG_PERIODIC      0x2     /* Periodic timing */
#define RT_TIMER_FLAG_ONE_SHOT      0x0     /* One shot timing */

// 1000 ticks is one second

/**
 * @brief 
 * 
 */
struct servo_motor {
    rt_thread_t servo_thread_calculate;
    rt_thread_t servo_thread_set;

    int servo_value[3];
};

typedef struct servo_motor *servo_motor_p;

/**
 * @brief 
 * 
 * @return int 
 */
int servo_init(void);

/**
 * @brief 
 * 
 * @param param 
 */
static void servo_set_positions(void *param);

/**
 * @brief 
 * 
 * @param param 
 */
static void servo_calculate_positions(void *param);


/**
 * @brief 
 * 
 * @param param 
 */
static void start_thread_set(void *param);

/**
 * @brief 
 * 
 * @param param 
 */
static void start_thread_calculate(void *param);

#endif /* APPLICATIONS_SERVO_H_ */
