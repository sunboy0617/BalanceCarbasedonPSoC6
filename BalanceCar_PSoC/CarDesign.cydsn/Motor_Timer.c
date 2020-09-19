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
#include "Motor_Timer.h"
#include "project.h"

#define MaxStep 800 //鍙互鍚庢湡淇敼鐨勬闀垮弬鏁?

void Motor_init()
{
    PWM_Right_Start();
    PWM_Left_Start();
    Cy_GPIO_Write(AIN1_PORT, AIN1_NUM, 0);
    Cy_GPIO_Write(AIN2_PORT, AIN2_NUM, 0);
    Cy_GPIO_Write(BIN1_PORT, BIN1_NUM, 0);
    Cy_GPIO_Write(BIN2_PORT, BIN2_NUM, 0);
}

void setPWM(int TargetRight, int TargetLeft)
{   
    static int StaRight=0;
    static int StaLeft=0;//琚瓨鍌ㄧ殑涓婁竴娆＄殑杞€?
    int Amplitude = 3000, 
    deadValueLeft = 40, //闃诲凹淇
    deadValueRight = 40;
    
    int left,right;
    if(TargetRight>=StaRight)
    {
        if(TargetRight>StaRight+MaxStep) right=StaRight+MaxStep;
        else right=TargetRight;
    }
    else
    {
        if(TargetRight<StaRight-MaxStep) right=StaRight-MaxStep;
        else right=TargetRight;
    }
    if(TargetLeft>=StaLeft)
    {
        if(TargetLeft>StaLeft+MaxStep) left=StaLeft+MaxStep;
        else left=TargetLeft;
    }
    else
    {
       if(TargetLeft<StaLeft-MaxStep) left=StaLeft-MaxStep;
        else left=TargetLeft;
    }
    StaLeft=left;
    StaRight=right;//淇濆瓨鐘舵€?
    
    if(left >= 0){//濡傛灉宸﹁疆杞€熷ぇ浜?
        Cy_GPIO_Write(BIN1_PORT, BIN1_NUM, 0);
        Cy_GPIO_Write(BIN2_PORT, BIN2_NUM, 1);
        if(left + deadValueLeft> Amplitude)
            Cy_TCPWM_PWM_SetCompare0(B_PWM_HW, B_PWM_CNT_NUM, Amplitude);//闄愬箙
        else
            Cy_TCPWM_PWM_SetCompare0(B_PWM_HW, B_PWM_CNT_NUM, left + deadValueLeft);
    }
    else{
        Cy_GPIO_Write(BIN1_PORT, BIN1_NUM, 1);
        Cy_GPIO_Write(BIN2_PORT, BIN2_NUM, 0);
       
        
        if(left - deadValueLeft < -Amplitude)
            Cy_TCPWM_PWM_SetCompare0(B_PWM_HW, B_PWM_CNT_NUM, Amplitude);
        else
            Cy_TCPWM_PWM_SetCompare0(B_PWM_HW, B_PWM_CNT_NUM, -left + deadValueLeft);//鎴栬鍙互鍔爋ffset
        

    }

    if(right >= 0){
        Cy_GPIO_Write(AIN1_PORT, AIN1_NUM, 1);
        Cy_GPIO_Write(AIN2_PORT, AIN2_NUM, 0);
        if(right + deadValueRight > Amplitude)
            Cy_TCPWM_PWM_SetCompare0(A_PWM_HW, A_PWM_CNT_NUM, Amplitude);
        else
            Cy_TCPWM_PWM_SetCompare0(A_PWM_HW, A_PWM_CNT_NUM, right + deadValueRight);
    }
    else{
        Cy_GPIO_Write(AIN1_PORT, AIN1_NUM, 0);
        Cy_GPIO_Write(AIN2_PORT, AIN2_NUM, 1);
        if(right - deadValueRight < -Amplitude)
            Cy_TCPWM_PWM_SetCompare0(A_PWM_HW, A_PWM_CNT_NUM, Amplitude);
        else
            Cy_TCPWM_PWM_SetCompare0(A_PWM_HW, A_PWM_CNT_NUM, -right + deadValueRight);

    }

    
    
}


/* [] END OF FILE */