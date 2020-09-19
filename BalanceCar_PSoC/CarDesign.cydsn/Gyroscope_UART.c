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

#include "Gyroscope_UART.h"
#include <stdio.h>

uint8_t receivedStringG52[11] = {0};
int receivedStartByteG52 = 0;
int receivedByteCountG52 = 0;
//Pitch angle
uint8_t receivedStringG53[11] = {0};
int receivedStartByteG53 = 0;
int receivedByteCountG53 = 0;
float Rollx, Pitchy, Yawz, Wx, Wy, Wz;
int inttime = 0;

void Gyroscope_UART_init()
{
    cy_en_scb_uart_status_t init_status;
        
    /* Start UART operation. */
    init_status = Cy_SCB_UART_Init(UART_1_HW, &UART_1_config, &UART_1_context);
    Cy_SCB_UART_Enable(UART_1_HW);  
    UART_1_HW->INTR_RX_MASK = SCB_INTR_RX_MASK_NOT_EMPTY_Msk;
    
    /* Interrupt Settings for UART */    
    Cy_SysInt_Init(&UART_1_SCB_IRQ_cfg, ISR_UART);
    
    /* Enable the interrupt */
    NVIC_EnableIRQ(UART_1_SCB_IRQ_cfg.intrSrc);
    
    __enable_irq(); /* Enable global interrupts. */
    
}

void ISR_UART(void)
{
    /* Check for "RX fifo not empty interrupt" */
    if((UART_1_HW->INTR_RX_MASKED & SCB_INTR_RX_MASKED_NOT_EMPTY_Msk ) != 0)
	{
        /* Clear UART "RX fifo not empty interrupt" */
		UART_1_HW->INTR_RX = UART_1_HW->INTR_RX & SCB_INTR_RX_NOT_EMPTY_Msk;        
            
        /* Get the character from terminal */
        uint8_t receivedByte;
        receivedByte = Cy_SCB_UART_Get(UART_1_HW);
        
        //printf("666\r\n");
        //Omega-W
        if(receivedByte == 0x52){
            receivedStartByteG52 = 1;
            receivedByteCountG52 = 0;
        }
        if(receivedStartByteG52 == 1){
            receivedStringG52[receivedByteCountG52++] = receivedByte;
        }
        if(receivedStartByteG52 == 1 && receivedByte == 0x55){
            uint8_t sum = 0x55, i;
            receivedStartByteG52 = 0;
            for(i = 0; i < 9; i++){
                sum += receivedStringG52[i];
            }
            if(sum == receivedStringG52[9]){
                Wx = (short)(((short)receivedStringG52[2] << 8) | receivedStringG52[1]) / 32768.0 * 2000;
                Wy = (short)(((short)receivedStringG52[4] << 8) | receivedStringG52[3]) / 32768.0 * 2000;
                Wz = (short)(((short)receivedStringG52[6] << 8) | receivedStringG52[5]) / 32768.0 * 2000;
            }
        }

        //Pitch angle
        if(receivedByte == 0x53){

            receivedStartByteG53 = 1;
            receivedByteCountG53 = 0;
        }
        if(receivedStartByteG53 == 1){
            receivedStringG53[receivedByteCountG53++] = receivedByte;
        }
        if(receivedStartByteG53 == 1 && receivedByte == 0x55){
            uint8_t sum = 0x55, i;
            receivedStartByteG53 = 0;
            for(i = 0; i < 9; i++){
                sum += receivedStringG53[i];
            }
            if(sum == receivedStringG53[9]){
                Rollx = (short)(((short)receivedStringG53[2] << 8) | receivedStringG53[1]) / 32768.0 * 180.0;
                Pitchy = (short)(((short)receivedStringG53[4] << 8) | receivedStringG53[3]) / 32768.0 * 180.0;
                Yawz = (short)(((short)receivedStringG53[6] << 8) | receivedStringG53[5]) / 32768.0 * 180.0;
                inttime++;
            }

        }
	}   
    else
    {
        /* Error if any other interrupt occurs */
        // uart_error = 1;
    }
    
}
