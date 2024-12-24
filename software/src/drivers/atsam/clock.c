#include "clock.h"
#include <stdint.h>

void configure_gclk_sources(void)
{
    // Set up GCLK0 for 48 MHz from the main system clock
    GCLK->GENCTRL[0].reg = GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_OSC8M;  // Use 8 MHz internal oscillator for GCLK0 (example)
    while (GCLK->SYNCBUSY.bit.GENCTRL0);  // Wait for synchronization
}

void disable_wdt(void) 
{
    WDT->CTRLA.ENABLE = 0;
    while (WDT->SYNCBUSY.bit.SYNCBUSY); /* sync */
}




