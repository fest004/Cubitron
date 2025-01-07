
#include "interrupt.h"


/* 
 * IMPORTANT! 
 *
 * this file assumes you have enabled EIC clock in cloc.c: something_init(void), 
* we will find out if init code in here needs to be before or after port configuration
*/



/* configures the different interrupt signals and priorities
*
* we have interrupts from servo controller, mby uart (prob not)
*, from IMU, ...
*/

void configure_eic(void)
{
    /* disable EIC while we configure it */
    EIC_REGS->EIC_CTRLA = EIC_CTRLA_ENABLE(0); /* clear enable bit */ 
    while (EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_ENABLE_Msk) 
    {
        /* Wait for synchronization */
    }

    /**************************/
    /* settings for interrupt */
    /**************************/

    /* EXTINT[3] -> Group 0, Pin 3 -> Rising edge */
    EIC_REGS->EIC_CONFIG[0] |= EIC_CONFIG_SENSE3_RISE;

    /* EXTINT[4] -> Group 1, Pin 4 -> Rising edge */
    EIC_REGS->EIC_CONFIG[0] |= EIC_CONFIG_SENSE4_RISE;

    /* EXTINT[5] -> Group 1, Pin 5 -> Rising edge */
    EIC_REGS->EIC_CONFIG[0] |= EIC_CONFIG_SENSE5_RISE;

    /* EXTINT[6] -> Group 1, Pin 6 -> Rising edge */
    EIC_REGS->EIC_CONFIG[0] |= EIC_CONFIG_SENSE6_RISE;

    /* EXTINT[7] -> Group 1, Pin 7 -> Rising edge */
    EIC_REGS->EIC_CONFIG[0] |= EIC_CONFIG_SENSE7_RISE;

    /*********************/
    /* Enable interrupts */
    /*********************/

    EIC_REGS->EIC_INTENSET = EIC_INTENSET_EXTINT(1 << 3) |  // Enable interrupt for EXTINT[3]
                             EIC_INTENSET_EXTINT(1 << 4) |  // Enable interrupt for EXTINT[4]
                             EIC_INTENSET_EXTINT(1 << 5) |  // Enable interrupt for EXTINT[5]
                             EIC_INTENSET_EXTINT(1 << 6) |  // Enable interrupt for EXTINT[6]
                             EIC_INTENSET_EXTINT(1 << 7);   // Enable interrupt for EXTINT[7]


    /*******************************************/
    /* Enable EIC after configuration complete */
    /*******************************************/
    EIC_REGS->EIC_CTRLA = EIC_CTRLA_ENABLE(1); 
    while (EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_ENABLE_Msk) 
    {
        /* Wait for synchronization */
    }

    /* missing nvic stuff? */
}

void ISR()
{
    
}
