#include "clock.h"
#include <stdint.h>

#define GCLK_SERCOM_SPI_GEN 1U  /* GCLK generator for SPI */
#define GCLK_SERCOM_I2C_GEN 2U  /* GCLK generator for I2C */
#define GCLK_SERCOM_UART_GEN 3U /* GCLK generator for UART */


/* configures main clock for the system */
void clk_init(void)
{
    disable_wdt();
    sys_clk_init();
    peripheral_clks_init();
}


/* sets system clock to 48MHz, configures DFLL &  */
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

    /* OSCCTRL_REGS->OSCCTRL_DFLLCTRLA = OSCCTRL_DFLLCTRLA_ENABLE_Msk | OSCCTRL_DFLLCTRLB_MODE_Msk | OSCCTRL_DFLLCTRLB_USBCRM_Msk; */

    while ((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_DFLLRDY_Msk) == 0) {}

    /* sse DFLL48M as GCLK0 src */
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_SRC(6U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_DIV(1U);
    while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK0) != 0) {}
}

/* sets up clocks for peripherals 
All I2C sercom peripherals can be on the same clock
All SPI sercom peripherals can be on the same clock
All UART sercom peripherals can be on the same clock
*/
void peripheral_clks_init(void)
{
    /* Section SPI configuration, for TMC & TMC_DB */

    /* selects glck1, SRC(6U) refers to DFLL48M for 48MHz, enables the clock, divides freq by 48 for 1 MHz signal */
    GCLK_REGS->GCLK_GENCTRL[GCLK_SERCOM_SPI_GEN] = GCLK_GENCTRL_SRC(6U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_DIV(48);
    while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK1) != 0) 
    {
	/* wait */
    }

    /* connects the clock to sercom4 (TMC_DEBUG sercom instance)*/
    GCLK_REGS->GCLK_PCHCTRL[4] = GCLK_PCHCTRL_GEN(GCLK_SERCOM_SPI_GEN) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[4] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk) 
    {
	/* wait */
    }

    /* connects the clock to sercom5 (TMC sercom instance)*/
    GCLK_REGS->GCLK_PCHCTRL[5] = GCLK_PCHCTRL_GEN(GCLK_SERCOM_SPI_GEN) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[5] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk) 
    {
	/* wait */
    }

    /* END OF SECTION SPI CLOCK CONFIGURATION */

    /******************************************************/
    /* Section I2C configuraiton, IMU1, IMU2, OLED screen */
    /* examples with OLED screen show CLK freq at 100KHz, this is within IMU accepted range, therefore we use 100 KHz */


    /* select gclk2, div by 480 ->  48MHz / 480 = 100 KHz */
    GCLK_REGS->GCLK_GENCTRL[2] = GCLK_GENCTRL_SRC(6U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_DIV(480);
    while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK2) != 0)
    {
	/* wait */
    }

    /* connect clock to sercom0 (IMU1) */
    GCLK_REGS->GCLK_PCHCTRL[0] = GCLK_PCHCTRL_GEN(GCLK_SERCOM_I2C_GEN) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[0] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk) 
    {
	/* wait */
    }

    /* connect clock to sercom1 (IMU2) */
    GCLK_REGS->GCLK_PCHCTRL[1] = GCLK_PCHCTRL_GEN(GCLK_SERCOM_I2C_GEN) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[1] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk) 
    {
	/* wait */
    }

    /* connect clock to sercom2 (OLED screen) */
    GCLK_REGS->GCLK_PCHCTRL[2] = GCLK_PCHCTRL_GEN(GCLK_SERCOM_I2C_GEN) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[2] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* wait */
    }

    /* END OF SECTION I2C CLOCK CONFIGURATION */

    /******************************************************/
    /* Section UART configuraiton, General DEBUG          */
    /******************************************************/

    /*
    Baudrate = Clock Freq / (Divisor * Oversampling Rate) 
    Assuming oversampling is 16, we can do 48 000 000 / (26 * 16) = 115200(within 1%)
    */

    GCLK_REGS->GCLK_GENCTRL[3] = GCLK_GENCTRL_SRC(6U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_DIV(26);
    while ((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL_GCLK3) != 0)
    {
	/* wait */
    }

    /* connect gclk3 to sercom3 (UART) */
    GCLK_REGS->GCLK_PCHCTRL[3] = GCLK_PCHCTRL_GEN(GCLK_SERCOM_UART_GEN) | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[3] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
	/* wait */
    }

    /* END OF SECTION UART CLOCK CONFIGURATION */
}


void enable_wdt(void)
{
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
    WDT_REGS->WDT_CTRLA &= ~WDT_CTRLA_ENABLE_Msk;
}


void clear_wdt(void)
{
    while (WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_CLEAR_Msk)
    {
	//wait
    }

    WDT_REGS->WDT_CLEAR = WDT_CLEAR_CLEAR_KEY;
}

