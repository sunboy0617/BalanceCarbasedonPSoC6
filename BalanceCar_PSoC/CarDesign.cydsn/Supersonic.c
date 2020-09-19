#include "Supersonic.h"
#include <stdio.h>
int count = 0 ;
float dist = 0;
static int rising = 1;
void Supersonic_Timer_init()
{
    
    /* Initialize and enable GPIO interrupt assigned to CM0+ */
    //SS_Timer_Enable();
    SS_PWM_Start();
    SS_Timer_Start();
    //Cy_GPIO_SetHSIOM(echo_pin_0_PORT,echo_pin_0_NUM, (en_hsiom_sel_t)echo_pin_0_INIT_MUXSEL);
    //Cy_GPIO_SetDrivemode(echo_pin_0_PORT,echo_pin_0_NUM, CY_GPIO_DM_PULLUP);
    //Cy_GPIO_SetVtrip(echo_pin_0_PORT,echo_pin_0_NUM, echo_pin_0_THRESHOLD_LEVEL);
    //Cy_GPIO_SetSlewRate(echo_pin_0_PORT,echo_pin_0_NUM, echo_pin_0_SLEWRATE);
    //Cy_GPIO_SetDriveSel(echo_pin_0_PORT,echo_pin_0_NUM, CY_GPIO_DRIVE_FULL);
    
    //Cy_GPIO_SetInterruptEdge(echo_pin_0_PORT,echo_pin_0_NUM, CY_GPIO_INTR_BOTH );
    //Cy_GPIO_SetInterruptMask(echo_pin_0_PORT,echo_pin_0_NUM, CY_GPIO_INTR_EN_MASK);
	Cy_SysInt_Init(&echo_cfg, SS_ISR);
    NVIC_ClearPendingIRQ(echo_cfg.intrSrc);
    NVIC_EnableIRQ(echo_cfg.intrSrc);
    /* Enale interrupt */
    //__enable_irq();
}

void SS_ISR()
{
    printf("fuck you !!!!\n");
    if(Cy_GPIO_GetInterruptStatus(echo_pin_0_PORT, echo_pin_0_NUM) == CY_GPIO_INTR_STATUS_MASK)
    {
        if(rising)
        {
            SS_Timer_SetCounter(0);
            //Cy_GPIO_SetInterruptEdge(echo_pin_0_PORT,echo_pin_0_NUM, CY_GPIO_INTR_FALLING);
            rising = 0;
        }
        else
        {
            //Cy_GPIO_SetInterruptEdge(echo_pin_0_PORT,echo_pin_0_NUM, CY_GPIO_INTR_RISING);
            rising = 1;
            count = SS_Timer_CNT_HW->COUNTER;
            dist = count*17000.0/50000000;
            printf("%d",count);
            printf("Distance: %f\n",dist);
        }
        Cy_GPIO_ClearInterrupt(echo_pin_0_PORT, echo_pin_0_NUM);
        NVIC_ClearPendingIRQ(echo_cfg.intrSrc);
    }
}
