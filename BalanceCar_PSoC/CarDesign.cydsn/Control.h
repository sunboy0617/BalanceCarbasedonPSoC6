/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/*
 * Control.h
 *
 *  Created on: 2019/3/21
 *      Author: Lewis Chen
 */

#ifndef HEADERS_USERS_CONTROL_H_
#define HEADERS_USERS_CONTROL_H_

//#include <./Headers/library.h>
//#include <./Headers/parameters.h>
#include <Motor_Timer.h>
#include <Encoder_Timer.h>
#include <Gyroscope_UART.h>
    
#define pitchyBias 1

#define deadValueL 20
#define deadValueR 60

#define Balance_Kp 180
#define Balance_Kd -12
#define Velocity_Kp 600
#define Turn_Kp 50

void carStop();
int balance();
int velocity();
int turn();
void turnleft();
void turnright();

#endif /* HEADERS_USERS_CONTROL_H_ */

/* [] END OF FILE */
