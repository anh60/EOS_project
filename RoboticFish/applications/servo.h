/**
 * @file servo.h
 * @author Maja Markusson
 * @brief Functions and objects to calculate and set the position of servo motors given preplanned
 *        positions in dregrees. The functionality is implemented using independent threads for the
 *        two tasks.
 * 
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <rtdef.h>
#include "base.h"

#ifndef APPLICATIONS_SERVO_H_
#define APPLICATIONS_SERVO_H_

#define STEPS_PER_REVOLUTION 10
#define TOTAL_SERVO_MOTORS 3
/**
 * @brief object describing a servo motor object as the parameters needs to be passed between the two threads.
 * 
 */
struct servo_motor {
    base_struct base;

    int servo_value_degrees[TOTAL_SERVO_MOTORS][STEPS_PER_REVOLUTION];
    int servo_value_pwm[TOTAL_SERVO_MOTORS];
};

typedef struct servo_motor *servo_motor_t;

servo_motor_t servo_init(void);
void servo_start(void *param);

#endif /* APPLICATIONS_SERVO_H_ */
