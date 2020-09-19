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
#ifndef SUPERSONIC_H_
#define SUPERSONIC_H_

//#include <library.h>
#include <Encoder_Timer.h>
#include <Motor_Timer.h>
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"

void Supersonic_Timer_init();
void SS_ISR();

#endif

/* [] END OF FILE */

