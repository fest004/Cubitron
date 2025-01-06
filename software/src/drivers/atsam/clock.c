#include "clock.h"
#include <stdint.h>

/* configures main clock for the system */

void clk_init(void)
{
    sys_clk_init();
    peripheral_clks_init();

}


/* sets system clock to 48MHz */
void sys_clk_init(void)
{
    /* configure GCLK0 to provide 32.768 kHz reference clock */
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_SRC(4U) | GCLK_GENCTRL_GENEN_Msk;
    while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK0) != 0) 
    {
	/* wait */
    }

    GCLK_REGS->GCLK_PCHCTRL[0] = GCLK_PCHCTRL_GEN(0U) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[0] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk) 
    {
	/* wait */
    }

    /* configure DFLL48M  for 48MHz */
    OSCCTRL_REGS->OSCCTRL_DFLLMUL = OSCCTRL_DFLLMUL_CSTEP(15) |
                                     OSCCTRL_DFLLMUL_FSTEP(255) |
                                     OSCCTRL_DFLLMUL_MUL(1465); /* 48MHz = 32.768KHz * 1465*/

    OSCCTRL_REGS->OSCCTRL_DFLLVAL = OSCCTRL_DFLLVAL_COARSE(32) | OSCCTRL_DFLLVAL_FINE(512);

    OSCCTRL_REGS->OSCCTRL_DFLLCTRLA = OSCCTRL_DFLLCTRLA_ENABLE_Msk | OSCCTRL_DFLLCTRLB_MODE_Msk | OSCCTRL_DFLLCTRLB_USBCRM_Msk;

    while ((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_DFLLRDY_Msk) == 0) {}

    /* sse DFLL48M as GCLK0 src */
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_SRC(6U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_DIV(1U);
    while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK0) != 0) {}
}

void peripheral_clks_init(void)
{

}

/* configures clocks for peripherals */

/* from datasheet: 
 
* Multiple instances of a peripheral will typically *
* have a separate Generic Clock for each instance.  *

which makes it a discussion on wether or not we should
have a clock for each peripheral, or if some peripherals
should share a clock (e.g IMUs share one clock, TMCs share another)

*/
void configure_gclk_sources(void)
{

    /* IMU clock */


    /* TMC clock */


    /* all the TMCs need to have an external clock on 25MHz */


    /* do my SERCOM modules need a clock? (yes) */
}

void enable_wdt(void)
{

    /* unsure if we need this check here. there is no syncbusy for the config register specifically it seems */
    while (WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Msk)
    {
	/*wait*/
    }

    /* setting the timeout cycle, completely arbitrary at 2048 atm */
    WDT_REGS->WDT_CONFIG = WDT_CONFIG_PER(WDT_CONFIG_PER_CYC2048);


    /* wait for the above operation to complete (if the above syncbusy check is unneeded, this might be as well) */
    while (WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Pos)
    {
	/*wait*/
    }

    WDT_REGS->WDT_CTRLA |= WDT_CTRLA_ENABLE_Msk;

    while (WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Pos)
    {
	/*wait*/
    }
}

void disable_wdt(void) 
{
    while (WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Pos)
    {
	/*wait*/
    }

    WDT_REGS->WDT_CTRLA &= WDT_CTRLA_ENABLE(0);
}


void clear_wdt(void)
{
    while (WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_CLEAR_Msk)
    {
	//wait
    }

    WDT_REGS->WDT_CLEAR = WDT_CLEAR_CLEAR_KEY;
}

