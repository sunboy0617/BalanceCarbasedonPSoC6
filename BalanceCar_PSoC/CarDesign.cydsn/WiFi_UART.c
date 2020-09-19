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
#include "WiFi_UART.h"
#include "stdio.h"

extern int turnrightflag,turnleftflag;
extern int turnleft90flag,turnright90flag;

float targetSpeed;

extern float speed,Encoder_Least, Encoder, Encoder_Integral,aimangle,InitEncoderIntegral;
extern int stopflag,Encoder_Integral_Flag;


//int getnewspeed()
void WiFi_UART_init()
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
        printf("Enter ISR wifiuart\r\n");
        receivedByte = Cy_SCB_UART_Get(UART_WIFI_HW);
        printf("Receivedbyte is %c\r\n",receivedByte);
        
          switch(receivedByte)
              {


        case 'w':
            targetSpeed = targetSpeed>=0?targetSpeed+15:15;
            
//            if(speed>=0)
//            {
//                for(int i = 0;i<150000;++i)
//                  {
//                    if(i%10000==0){
//                    ++speed;}
//                  }
//               
//            }
//            else 
//            {
//                //speed = 15;
//                while(speed!=15)
//                {
//                    int i = 0;
//                    while((++i)<=10000);
//                    ++speed;
//                }
//                
//            }
            Encoder_Integral_Flag=0;
           
            break;

        case 's':
            targetSpeed=targetSpeed<=0?(targetSpeed-15):(-15);
             
//            if(speed<=0)
//            {
//              for(int j = 0;j<150000;++j)
//                 if(j%10000==0)
//                  --speed;
//            }
//            else {
//                
//                 while(speed!=-15)
//                  { 
//                    int i = 0;
//                    while((++i)<=10000);
//                    --speed;
//                  }
//            }
            Encoder_Integral_Flag=0;
           
            break;
        case 'p':
            targetSpeed=0;
            break;
        case 'a':
            turnleft90flag=1;
            break;
        case 'd':
            turnright90flag=1;
            break;
        case 'i':
            if(targetSpeed!=0)
            {
                targetSpeed=targetSpeed>0?(targetSpeed-15):(targetSpeed+15);
            }
            break;
        case 'z':
            turnleft90flag=1;
            break;
        case 'c':
            turnright90flag=1;
            break;
        default:
            break;




        }
    }
}
/* [] END OF FILE */
