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
 * Control.c
 *
 *  
 *      Author: lch
 */
#include <Control.h>
#include <stdio.h>

//Start or stop flag
int start = 0;
/* Wrong data from the gyroscope may be received to make the car stop,
     this records the number of data */
int errorCount = 0;
/*The expected speed and turnAngle,
 * your functions should change the two variables to control the car */
static float speed = 0;
float turnAngle = 0;
extern float Encoder_Integral_Flag;
extern int sendflag;
extern char sendchar;
extern float distance;
extern float Rollx,Wx,speedNLeft,speedNRight;
extern float targetSpeed;

float Encoder_Least=0, Encoder=0, Encoder_Integral=0;


float aimangle=0;
float turn_integral=0;


void carStop(){
    
    Cy_TCPWM_PWM_SetCompare0(A_PWM_HW, A_PWM_CNT_NUM, 0);
    Cy_TCPWM_PWM_SetCompare0(B_PWM_HW, B_PWM_CNT_NUM, 0);
    
    errorCount = 0;
    Encoder_Integral=0;
    turn_integral=0;
    speed=0;
}

//Balance PID
float kp_b = 340, kd_b = 22/*19*/ , ld=0.0;//370
float kp_v_f = 700, ki_v_f = 8.5;
float kp_v_b = 740, ki_v_b = 8.5;
float kp_t=-100,ki_t=-20;

int balance(){


    float Bias;
    int balance;
    //printf("error: %d \r\n", errorCount);
    //printf("");
    printf("Rollx: %f \r\n", Rollx);
    if(Rollx > 50 || Rollx < -50){
        errorCount++;
        //Rollx=0;
    }
    else if(errorCount < 10){
        errorCount = 0;
    }

    if(errorCount >= 10){
        errorCount = 0;
        Encoder_Integral=0;
        turn_integral=0;
        speed=0;
        start = 0;
    }

    Bias = Rollx - ld;

    balance = kp_b * Bias + Wx * kd_b;
    //printf("Wx: %.3f", Wx);
    
    printf("balance: %d", balance);

    return balance;

}

//Velocity PID

/*
 *
 */int velocity(){
     float Velocity;
     if(speed<targetSpeed)
       speed+=0.1;
     else if(speed>targetSpeed)
       speed-=0.1;
    //计算速度偏差
     Encoder_Least = speedNLeft + speedNRight; //+ speed / -40.0;
     
     if((Encoder_Least<0&&speed>0)||(Encoder_Least>0&&speed<0))
     {
         Encoder_Least +=speed /-15.0;
     }
     else
     {
         Encoder_Least +=speed / -40.0;
     }
    //低通滤波，积分
     Encoder *= 0.70;
     Encoder+= Encoder_Least * 0.30;
//     Encoder_Integral += Encoder_Integral_Flag?Encoder:0;
    
    
     Encoder_Integral+=Encoder+speed*(-0.02);
     distance+=0.0275*speed;//�ƾ���

     /*
     if(distance>150)
     {
         distance=0;
         speed=0;
     }*/


     if(Encoder_Integral > 500)
         Encoder_Integral = 500;
     if(Encoder_Integral < -500)
         Encoder_Integral = -500;
    
    if(speed>0)
      Velocity = Encoder* kp_v_f + Encoder_Integral * ki_v_f;
    else 
      Velocity = Encoder* kp_v_b + Encoder_Integral * ki_v_b;
     return Velocity;
 }


//Turning PID

int turn(){
    float Turn;
    //Bias = Yawz - turnAngle;
    turn_integral+=(-speedNLeft+speedNRight+aimangle);
    aimangle=0;
    Turn = turn_integral*ki_t+(-speedNLeft+speedNRight)*kp_t;
    return Turn;
}


//ת90�Ⱥ���
extern int turnleft90flag,turnright90flag;
void turnleft()
{
    
    static int i=0;
    i++;
    aimangle+=1;
    if(i>=250)
    {
        i=0;
        turnleft90flag=0;
        
    }
}
// ����230�ξʹ�ſ�����

void turnright()
{
    
    static int i=0;
    i++;
    aimangle-=1;
    if(i>=250)
    {
        i=0;
        turnright90flag=0;
        
    }
}





/* [] END OF FILE */
