/**
 * \file
 *
 * \brief System configuration file for ATSAMD11D14AM
 *
 * Copyright (c) 2022 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

#include "samd11d14am.h"

/** \cond 0 */
/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */
/** \endcond */

/**
 * Initial system clock frequency. The System RC Oscillator (RCSYS) provides
 *  the source for the main clock at chip startup.
 */
#define __SYSTEM_CLOCK    (48000000)
uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/

/**
 * Initialize the system
 *
 * \brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
void SystemInit(void)
{
    SYSCTRL_REGS->SYSCTRL_INTFLAG = SYSCTRL_INTFLAG_BOD33RDY_Msk | SYSCTRL_INTFLAG_BOD33DET_Msk | SYSCTRL_INTFLAG_DFLLRDY_Msk;
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(2); // read wait states

    SYSCTRL_REGS->SYSCTRL_DFLLCTRL = 0; // See Errata 9905
    while (0 == (SYSCTRL_REGS->SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY_Msk));

    uint32_t coarse = (OTP4_FUSES_REGS->FUSES_OTP4_WORD_1 & FUSES_OTP4_WORD_1_DFLL48M_COARSE_CAL_Msk) >> FUSES_OTP4_WORD_1_DFLL48M_COARSE_CAL_Pos;
    uint32_t fine   = (OTP4_FUSES_REGS->FUSES_OTP4_WORD_2 & FUSES_OTP4_WORD_2_DFLL48M_FINE_CAL_Msk) >> FUSES_OTP4_WORD_2_DFLL48M_FINE_CAL_Pos;
    SYSCTRL_REGS->SYSCTRL_DFLLMUL = SYSCTRL_DFLLMUL_MUL(48000);
    SYSCTRL_REGS->SYSCTRL_DFLLVAL = SYSCTRL_DFLLVAL_COARSE(coarse) | SYSCTRL_DFLLVAL_FINE(fine);

    SYSCTRL_REGS->SYSCTRL_DFLLCTRL = SYSCTRL_DFLLCTRL_ENABLE_Msk | SYSCTRL_DFLLCTRL_USBCRM_Msk | SYSCTRL_DFLLCTRL_BPLCKC_Msk | SYSCTRL_DFLLCTRL_CCDIS_Msk | SYSCTRL_DFLLCTRL_STABLE_Msk;

    while (0 == (SYSCTRL_REGS->SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY_Msk));// // wait till DFLL is stable and ready to be used as a clock source

    GCLK_REGS->GCLK_GENDIV = GCLK_GENDIV_ID(GCLK_CLKCTRL_GEN_GCLK0_Val) | GCLK_GENDIV_DIV(1);
    GCLK_REGS->GCLK_GENCTRL = GCLK_GENCTRL_ID (GCLK_CLKCTRL_GEN_GCLK0_Val) | GCLK_GENCTRL_SRC (GCLK_SOURCE_DFLL48M) | GCLK_GENCTRL_RUNSTDBY(1) | GCLK_GENCTRL_GENEN(1);
    while (GCLK_REGS->GCLK_STATUS & GCLK_STATUS_SYNCBUSY(1));
    return;
}

/**
 * Update SystemCoreClock variable
 *
 * \brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
void SystemCoreClockUpdate(void)
{
    // Not implemented
    SystemCoreClock = __SYSTEM_CLOCK;
    return;
}

/** \cond 0 */
/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */
/** \endcond */
