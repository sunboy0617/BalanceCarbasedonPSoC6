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

#ifndef HEADERS_DRIVERS_WI_FI_UART_H_
#define HEADERS_DRIVERS_WI_FI_UART_H_

#include "project.h"

//#include <library.h>

//Variables in UART IRQHandler to handle data of Wi-fi UART module
extern uint8_t newLineReceived;
extern uint8_t receivedString[100];
extern int receivedStringLength;

void WiFi_UART_init();
void ISR_UART_WiFi(void);
//int fputc(int _c, register FILE *_fp);
//int fputs(const char *_ptr, register FILE *_fp);

#endif /* HEADERS_DRIVERS_WI_FI_UART_H_ */


/* [] END OF FILE */
