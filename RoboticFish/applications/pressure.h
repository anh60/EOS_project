/**
 * @file pressure.h
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
#ifndef APPLICATIONS_PRESSURE_H_
#define APPLICATIONS_PRESSURE_H_

#define RT_TIMER_FLAG_PERIODIC      0x2     /* Periodic timing     */

/**
 * @brief initialization and startup function for the pressure module.
 *        Activates the timer, event and thread needed. Does some light error detection.
 * 
 * @return int
 *          0 - no errors
 *         -1 - event init error 
 *         -2 - thread startup error 
 *         -3 - timer startup error
 */
int pressure_init(void);

/**
 * @brief Mock function to simulate pressure sersor input data. 
 * 
 * @return int - random integer in the range 0-1024.
 */
static int pressure_get(void);

/**
 * @brief Function storing pressure data to sector 4 of the microcontroller
 *        flash memory. Remark: if the value is to be read out again the 
 *        bits need to be rearranged in the correct edian as usual when working 
 *        with flash memory. 
 * 
 * @param pressure 32 bit integer
 */
static void pressure_store(u_int32_t pressure);

/**
 * @brief Thread using functions pressure_get and pressure_store to
 *        read and store pressure sensor data. Triggered periodically in 
 *        periods of 75 ms. 
 * 
 * @param param 
 */
static void pressure_handler(void *param);

/**
 * @brief Function triggered by the correlating timer to send an event to the suspended thread. 
 * 
 * @param param pressure object. 
 */
static void start_thread(void *param);



#endif /* APPLICATIONS_PRESSURE_H_ */
