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
#include "project.h"
#include <stdio.h>
#include "Gyroscope_UART.h"
#include "Encoder_Timer.h"
#include "Motor_Timer.h"
#include "CarTask.h"
#include "WiFi_UART.h"
#include "Supersonic.h"


extern int inttime;
extern int start;
extern float Rollx, Pitchy, Yawz, Wx, Wy, Wz;
extern int countRight, advanceOrBackRight, countLeft, advanceOrBackLeft;

float distance = 0.10;
int turnleftflag = 0, turnrightflag = 0;

float Encoder_Integral_Flag=1;

int turnleft90flag=0,turnright90flag=0;
void print_task()
{
    for(;;)
    {
        /* Place your application code here. */

        if(countRight % 20000 == 0)
        {
            printf("rollx: %f, yawz: %f, pitchy: %f, wx: %f, wy: %f, wz: %f\r\n", Rollx, Yawz, Pitchy, Wx, Wy, Wz);   
            printf("countRight: %d\r\n", countRight);
            printf("Direction: %d\r\n", advanceOrBackRight);
            printf("countLeft: %d\r\n", countLeft);
            printf("Direction: %d\r\n", advanceOrBackLeft);
            printf("\r\n");
        }
        //taskYIELD();
    }
}

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    UART_COMP_Start();
    
    printf("Psoc has started!\r\n");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */


    Motor_init();
    Gyroscope_UART_init();
    WiFi_UART_init();
    Encoder_Timer_init();
    Supersonic_Timer_init();
    
    
    
    
    //setPWM(3000, 3000);
    
    start = 1;
    
    xTaskCreate(T32_Task, "T32_task", configMINIMAL_STACK_SIZE * 8, 0,3,0);
    //xTaskCreate(print_task, "print_task", configMINIMAL_STACK_SIZE * 8,0,3,0);
    vTaskStartScheduler();

    for(;;)
    {
        /* Place your application code here. */

        if(countRight % 20000 == 0)
        {
            printf("rollx: %f, yawz: %f, pitchy: %f, wx: %f, wy: %f, wz: %f\r\n", Rollx, Yawz, Pitchy, Wx, Wy, Wz);   
            printf("countRight: %d\r\n", countRight);
            printf("Direction: %d\r\n", advanceOrBackRight);
            printf("countLeft: %d\r\n", countLeft);
            printf("Direction: %d\r\n", advanceOrBackLeft);
            printf("\r\n");
        }
    }
}

/* [] END OF FILE */
