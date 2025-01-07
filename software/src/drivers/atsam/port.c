#include "port.h"


void ports_init(void) 
{
    /*******************/
    /* LED PINS SECTION*/
    /*******************/

    /* status 1-3 pins */
    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 22); /* Set direction to output for PB22 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 22); /* set it to 0 */

    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 23); /* Set direction to output for PB23 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 23); /* set it to 0 */

    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 27); /* Set direction to output for PA27 */
    PORT_REGS->GROUP[0].PORT_OUTCLR = (1 << 27); /* set it to 0 */

    /* error led, process led */
    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 0); /* Set direction to output for PA00 */
    PORT_REGS->GROUP[0].PORT_OUTCLR = (1 << 0); /* Set it to zero */

    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 1); /* Set direction to output for PA01 */
    PORT_REGS->GROUP[0].PORT_OUTCLR = (1 << 1); /* Set it to zero */

    /*******************/
    /* SERCOM SECTION  */
    /*******************/

    /* configure I2C for IMU1 (SERCOM0) */
    configure_pin(0, 8, 0x2);  // PA08
    configure_pin(0, 9, 0x2);  // PA09

    /* configure I2C for IMU2 (SERCOM1) */
    configure_pin(0, 16, 0x2); // PA16
    configure_pin(0, 17, 0x2); // PA17

    /* Configure I2C for OLED (SERCOM2) */
    configure_pin(0, 12, 0x2); // PA12
    configure_pin(0, 13, 0x2); // PA13

    /* Configure UART for Debug (SERCOM3) */
    configure_pin(0, 18, 0x3); // PA18
    configure_pin(0, 19, 0x3); // PA19

    /* Configure SPI for TMC Debug (SERCOM4) */
    configure_pin(1, 12, 0x2); // PB12
    configure_pin(1, 13, 0x2); // PB13
    configure_pin(1, 14, 0x2); // PB14

    /* Configure SPI for TMC Functional (SERCOM5) */
    configure_pin(0, 23, 0x3); // PA23
    configure_pin(0, 24, 0x3); // PA24
    configure_pin(0, 25, 0x3); // PA25

    /* set all CHIP SELECTS as output, and init to 0 */
    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 3); /* Set direction to output for PB03 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 3); /* Set it to zero */

    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 2); /* Set direction to output for PB02 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 2); /* Set it to zero */

    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 1); /* Set direction to output for PB01 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 1); /* Set it to zero */

    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 0); /* Set direction to output for PB00 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 0); /* Set it to zero */

    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 31); /* Set direction to output for PB31 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 31); /* Set it to zero */

    PORT_REGS->GROUP[1].PORT_DIRSET = (1 << 30); /* Set direction to output for PB30 */
    PORT_REGS->GROUP[1].PORT_OUTCLR = (1 << 30); /* Set it to zero */


    /*******************/
    /* PWM SECTION     */
    /*******************/
    /* servo pwm controller pwm pins, TCC for PWM control, which is group F -> 0x5*/
    configure_pin(0, 20, 0x5);
    configure_pin(0, 21, 0x5);
    configure_pin(0, 22, 0x5);


    /*******************/
    /*INTERRUPT SECTION*/
    /*******************/
    /* EIC for interrupt, which is group A -> 0x0 */


    /* interrupt for servo controller status pins */
    configure_pin(0, 3, 0x0);
    PORT_REGS->GROUP[0].PORT_PINCFG[3] |= PORT_PINCFG_INEN_Msk;

    configure_pin(1, 4, 0x0);
    PORT_REGS->GROUP[1].PORT_PINCFG[4] |= PORT_PINCFG_INEN_Msk;

    configure_pin(1, 5, 0x0);
    PORT_REGS->GROUP[1].PORT_PINCFG[5] |= PORT_PINCFG_INEN_Msk;


    /* interrupt from imu data rdy */
    configure_pin(1, 6, 0x0);
    PORT_REGS->GROUP[1].PORT_PINCFG[6] |= PORT_PINCFG_INEN_Msk;

    configure_pin(1, 7, 0x0);
    PORT_REGS->GROUP[1].PORT_PINCFG[7] |= PORT_PINCFG_INEN_Msk;

}


/* helper function to configure a given pin 
group = 0 -> Port Group A
group = 1 -> Port Group B
pin = x -> pin x in group chosen 
pmux_function = x -> pmux table function offset by x, refer to datasheet port multiplexing 

popular options: 
A = External Interrupt Controller -> 0x0 (offset 0)
C/D = SERCOM -> 0x2/0x3 (both C and D are SERCOM)
F = TCC/PWM -> 0x5 
*/
void configure_pin(uint8_t group, uint8_t pin, uint8_t pmux_function) 
{
    PORT_REGS->GROUP[group].PORT_PINCFG[pin] |= PORT_PINCFG_PMUXEN_Msk;
    uint8_t pmux_index = pin / 2;
    if (pin % 2 == 0) 
    {
        PORT_REGS->GROUP[group].PORT_PMUX[pmux_index] = (PORT_REGS->GROUP[group].PORT_PMUX[pmux_index] & ~PORT_PMUX_PMUXE_Msk) |
												PORT_PMUX_PMUXE(pmux_function);
    } 
    else 
    {
        PORT_REGS->GROUP[group].PORT_PMUX[pmux_index] = (PORT_REGS->GROUP[group].PORT_PMUX[pmux_index] & ~PORT_PMUX_PMUXO_Msk) |
												PORT_PMUX_PMUXO(pmux_function);
    }
}

