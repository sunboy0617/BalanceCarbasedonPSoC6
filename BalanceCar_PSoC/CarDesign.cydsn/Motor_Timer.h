/*
 * Motor_Timer_A.h
 *
 *  Created on: 2019/3/21
 *      Author: Lewis Chen
 */

#ifndef _MOTOR_TIMER_H_
#define _MOTOR_TIMER_H_
    
#include "project.h"

#define AIN1_PORT   A0_0_PORT
#define AIN1_NUM    A0_0_NUM
#define AIN2_PORT   A1_0_PORT
#define AIN2_NUM    A1_0_NUM
#define BIN1_PORT   B0_0_PORT
#define BIN1_NUM    B0_0_NUM
#define BIN2_PORT   B1_0_PORT
#define BIN2_NUM    B1_0_NUM
    
#define A_PWM               PWM_Right
#define B_PWM               PWM_Left
#define A_PWM_HW            PWM_Right_HW
#define B_PWM_HW            PWM_Left_HW
#define A_PWM_CNT_NUM       PWM_Right_CNT_NUM
#define B_PWM_CNT_NUM       PWM_Left_CNT_NUM
    
//Constrain and set PWM
void setPWM(int left,int right);
void Motor_init();


#endif /* HEADERS_DRIVERS_MOTOR_TIMER_A_H_ */
