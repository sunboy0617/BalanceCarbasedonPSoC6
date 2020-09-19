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

#include "WiFi-UART.h"

extern int turnrightflag,turnleftflag;
extern int turnleft90flag,turnright90flag;
extern int autoflag;

extern float speed,Encoder_Least, Encoder, Encoder_Integral,aimangle,InitEncoderIntegral;
extern int sendflag,stopflag,Encoder_Integral_Flag;
extern char sendchar;
extern int flag1,flag2,flag3;

void WiFi_UART_Init()
{
    cy_en_scb_uart_status_t init_status;
        
    /* Start UART operation. */
    init_status = Cy_SCB_UART_Init(UART_WIFI_HW, &UART_WIFI_config, &UART_WIFI_context);
    Cy_SCB_UART_Enable(UART_WIFI_HW);  
    UART_WIFI_HW->INTR_RX_MASK = SCB_INTR_RX_MASK_NOT_EMPTY_Msk;
    
    /* Interrupt Settings for UART */    
    Cy_SysInt_Init(&UART_WIFI_SCB_IRQ_cfg, ISR_UART_WiFi);
    
    /* Enable the interrupt */
    NVIC_EnableIRQ(UART_WIFI_SCB_IRQ_cfg.intrSrc);
    
    __enable_irq(); /* Enable global interrupts. */
}

void ISR_UART_WiFi(void)
{
    /* Check for "RX fifo not empty interrupt" */
    if((UART_WIFI_HW->INTR_RX_MASKED & SCB_INTR_RX_MASKED_NOT_EMPTY_Msk ) != 0)
	{
        /* Clear UART "RX fifo not empty interrupt" */
		UART_WIFI_HW->INTR_RX = UART_WIFI_HW->INTR_RX & SCB_INTR_RX_NOT_EMPTY_Msk;        
            
        /* Get the character from terminal */
        uint8_t receivedByte;
        receivedByte = Cy_SCB_UART_Get(UART_WIFI_HW);
        
        switch(receivedByte)
        {


        case 'w':
            speed=speed>=0?(speed+15):15;
            Encoder_Integral_Flag=0;
            if(speed>=0){
                sendchar=speed/15+'0';
                sendflag=1;
            }
            else{
                sendchar=-speed/15+'0';
                sendflag=1;
            }
            break;

        case 's':
            speed=speed<=0?(speed-15):(-15);
            Encoder_Integral_Flag=0;
            if(speed>=0){
                sendchar=speed/15+'0';
                sendflag=1;
            }
            else{
                sendchar=-speed/15+'0';
                sendflag=1;
            }

            break;
        case 'p':
            //stopflag=1;
            speed=0;
            sendchar='0';
            sendflag=1;
            break;
        case 'a':
            turnleftflag=1;
            //sendchar='a';
            //sendflag=1;
            break;
        case 'd':
            turnrightflag=1;
            //aimangle=-10;
            //sendchar='d';
            //sendflag=1;
            break;
        case 'i':
            if(speed!=0)
            {
                speed=speed>0?(speed-15):(speed+15);
            }
            sendchar='i';
            sendflag=1;
            break;
        case 'z':
            turnleft90flag=1;
            sendchar='L';
            sendflag=1;
            break;
        case 'c':
            turnright90flag=1;
            sendchar='R';
            sendflag=1;
            break;
//        case 'k':
//            keepstraightflag=1-keepstraightflag;
//            sendchar=keepstraightflag?'k':'N';
//            sendflag=1;
//            break;
//        case 'v':
//            SuperVoiceflag^=1;
//            sendchar=SuperVoiceflag+'N';
//            sendflag=1;
//            break;
        case'o'://一键启动自动
            autoflag^=1;

            //SuperVoiceflag=autoflag;
            //keepstraightflag=autoflag;
            speed=30*autoflag;
            sendchar=autoflag?'O':'N';
            sendflag=1;
            break;

        case '1':
            flag1=1;
            flag2=0;
            flag3=0;
            sendchar='1';
            sendflag=1;
            break;
        case '2':
            flag1=0;
            flag2=1;
            flag3=0;
            sendchar='2';
            sendflag=1;
            break;
        case '3':
            flag1=0;
            flag2=0;
            flag3=1;
            sendchar='3';
            sendflag=1;
            break;



        }
    }
}

