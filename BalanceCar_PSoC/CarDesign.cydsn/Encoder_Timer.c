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

/* [] END OF FILE */
#include "Encoder_Timer.h"
#include <stdio.h>

//Record the number of rising edge captured
int countLeft = 0, lastCountLeft = 0, countRight = 0, lastCountRight = 0;
//Forward or backward flag
uint8_t advanceOrBackLeft = 0, advanceOrBackRight = 0;
//Rotational Speed-N
float speedNLeft = 0, speedNRight = 0;
int count;

void Encoder_Timer_init()
{
    Right_Encoder_Counter_Start();
    Cy_SysInt_Init(&Right_Encoder_Int_cfg, Right_Encoder_ISR);
    NVIC_EnableIRQ(Right_Encoder_Int_cfg.intrSrc);
    
    Left_Encoder_Counter_Start();
    Cy_SysInt_Init(&Left_Encoder_Int_cfg, Left_Encoder_ISR);
    NVIC_EnableIRQ(Left_Encoder_Int_cfg.intrSrc);
    
    __enable_irq(); /* Enable global interrupts. */
    
}

void Right_Encoder_ISR()
{
    advanceOrBackRight = Cy_GPIO_Read(Right_B_0_PORT, Right_B_0_NUM);
    countRight += 100;
    
    Right_Encoder_Counter_ClearInterrupt(CY_TCPWM_INT_ON_CC); 
    
}
void Left_Encoder_ISR()
{
    advanceOrBackLeft = Cy_GPIO_Read(Left_B_0_PORT, Left_B_0_NUM);
    countLeft += 100;
    Left_Encoder_Counter_ClearInterrupt(CY_TCPWM_INT_ON_CC);
    
    
}
