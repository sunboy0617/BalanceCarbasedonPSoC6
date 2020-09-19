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

#include "CarTask.h"
#include <stdio.h>

int b,v,t;
//Rotational Speed-N
extern float speedNLeft, speedNRight;
//
extern int turnleft90flag,turnright90flag;
extern float aimangle;
extern int turnleftflag,turnrightflag;
extern int start;
extern float Rollx;
extern int countLeft,lastCountLeft,advanceOrBackLeft,countRight,lastCountRight,advanceOrBackRight;
extern int pointer;
extern float targetSpeed;
//
//Used to be void T32_INT1_IRQHandler(void),interrupt change to task

extern float dist;

static int warning_count=0;
void T32_Task()
{

    

    float tempSpeedN = 0;
    static int PWMLeft, PWMRight;
    
    while(1)

    //Calculate the rotational speed of left motor
    {
        tempSpeedN = (countLeft - lastCountLeft) / 15000.0 * 200.0;
        if(tempSpeedN >= 0){
            if(advanceOrBackLeft == 1)
                speedNLeft = tempSpeedN;
            else
                speedNLeft = -tempSpeedN;
        }
        lastCountLeft = countLeft;

        //Calculate the rotational speed of right motor
        tempSpeedN = (countRight - lastCountRight) / 15000.0 * 200.0;
        if(tempSpeedN >= 0){
            if(advanceOrBackRight == 1)
                speedNRight = -tempSpeedN;
            else
                speedNRight = tempSpeedN;
        }
        lastCountRight = countRight;
        
        if(start)
        {
            if(dist < 30)
            {
                warning_count++;
            }
            else
            {
                warning_count = warning_count>0? warning_count-1 : 0;
            }
            
            if(warning_count >= 5)
            {
                targetSpeed = 0;
                warning_count = 0;
            }
            b=balance();
            v=velocity();
            
            printf("vel: %d\r\n",v);
            t=turn();

            PWMLeft = 1 * b - 1 * v + 1 * t;
            PWMRight = 1 * b - 1 * v - 1 * t;

            printf("PWMLeft: %d", PWMLeft);
            printf("PWMRight: %d", PWMRight);
            setPWM(PWMRight, PWMLeft);

            if(turnleft90flag)
                turnleft();
            if(turnright90flag)
                turnright();
            
            }
            else{
                carStop();
                
                
                
            }
            
            taskYIELD();
        
        
    }
        
        
    
}

/* [] END OF FILE */
