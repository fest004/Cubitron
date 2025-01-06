#include "sercom.h"


void enable_sercom_instances(void)
{
    //MCLK->APBAMASK.bit.SERCOM0_ = 1;
    //MCLK->APBBMASK.bit.SERCOM1_ = 1;
    //MCLK->APBCMASK.bit.SERCOM2_ = 1;
    //MCLK->APBCMASK.bit.SERCOM3_ = 1;
    // MCLK->APBCMASK.bit.SERCOM4_ = 1;
    // MCLK->APBCMASK.bit.SERCOM5_ = 1;
}

/*
This function sets up each PIN to its corresponding SERCOM instance. Each pin requires two configuration lines. 
The process is as follows:

### Line 1:
PORT->Group[n]
- This refers to groups of pins. For example:
  - Group[0] corresponds to pins PA00–PA31.
  - Group[1] corresponds to pins PB00–PB31.
- `.PINCFG[m]` selects the specific pin within the group. For instance:
  - PA08 corresponds to PINCFG[8].
- `.bit.PMUXEN = 1` enables peripheral multiplexing, changing the pin from GPIO to a specialized function (e.g., SERCOM, interrupt).

**Purpose**: This line enables the pin to function as something other than GPIO.

### Line 2:
PORT->Group[n]
- Same as above, this refers to the group and pin being configured.
- `.PMUX[k].bit.PMUXE/PMUXO` selects the function for the specific pin:
  - Divide the pin number by 2 to determine the PMUX register:
    - Example: For PA08, `8 ÷ 2 = PMUX[4]`.
  - Use `.PMUXE` for even-numbered pins (e.g., PA08).
  - Use `.PMUXO` for odd-numbered pins (e.g., PA09).

- The value assigned (e.g., `0x2`) specifies the peripheral function:
  - `0x0`: Function A
  - `0x1`: Function B
  - `0x2`: Function C (e.g., SERCOM0 PAD[0] for PA08).

### Key Considerations:
1. **I2C**: For I2C, the `PAD` assignments are fixed:
   - SDA is always PAD[0].
   - SCL is always PAD[1].
   - Check the datasheet for compatible pin and SERCOM configurations.
2. **SPI & USART**: Any pin with SERCOM functionality can be used, but ensure all required signals (e.g., RX/TX for USART, SCK/MOSI/MISO for SPI) are mapped to the same SERCOM instance.

This general pattern applies to all SERCOM configurations, with pin groups and peripheral functions varying based on your specific setup.
*/


#if 0

void sercom_multipexing(void)
{

	/*  ---- SERCOM0 ---- */
	/* Setting PA08 and PA09 for I2C communication with IMU nr 1 */

	PORT->Group[0].PINCFG[8].bit.PMUXEN = 1;  // Enable peripheral multiplexer for PA08
	PORT->Group[0].PMUX[4].bit.PMUXE = 0x2;   // Set PA08 to PMUX function C (SERCOM0 PAD[0])

	PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;  // Enable peripheral multiplexer for PA09
	PORT->Group[0].PMUX[4].bit.PMUXO = 0x2;   // Set PA09 to PMUX function C (SERCOM0 PAD[1])

	/*  ---- SERCOM1 ---- */
	/* Setting PA16 and PA17 for I2C communication with IMU nr 2 */

	PORT->Group[0].PINCFG[16].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[8].bit.PMUXE = 0x2;

	PORT->Group[0].PINCFG[17].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[8].bit.PMUXO = 0x2;


	/*  ---- SERCOM2 ---- */
	/* Setting PA12 and PA13 for I2C communication with OLED screen */

	PORT->Group[0].PINCFG[12].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[6].PMUXE = 0x2;

	PORT->Group[0].PINCFG[13].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[6].PMUXO = 0x2;


	/*  ---- SERCOM3 ---- */
	/* Setting PA18 and PA19 for USART debug communication external terminal */

	PORT->Group[0].PINCFG[18].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[9].bit.PMUXE = 0x3; /* Group D for SERCOM3 */

	PORT->Group[0].PINCFG[19].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[9].bit.PMUXO = 0x3;


	
	/*  ---- SERCOM4 ---- */
	/* Setting PB12, PB13 and PB13 for debug SPI communication with TMC4671s */

	PORT->Group[1].PINCFG[12].bit.PMUXEN = 1;
	PORT->Group[1].PMUX[6].bit.PMUXE = 0x2;

	PORT->Group[1].PINCFG[13].bit.PMUXEN = 1;
	PORT->Group[1].PMUX[6].bit.PMUXO = 0x2;


	PORT->Group[1].PINCFG[14].bit.PMUXEN = 1;
	PORT->Group[1].PMUX[7].bit.PMUXE = 0x2;


	/*  ---- SERCOM5 ---- */
	/* Setting PA23, PA24 and PA25 for functional SPI communication with TMC4671s */

	PORT->Group[0].PINCFG[23].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[11].bit.PMUXO = 0x3;

	PORT->Group[0].PINCFG[24].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[12].bit.PMUXE = 0x3;


	PORT->Group[0].PINCFG[25].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[12].bit.PMUXO = 0x3;
}

#endif
