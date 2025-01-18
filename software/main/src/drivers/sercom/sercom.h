
/*

Atsam has 8 different sercoms. We use SERCOM[0, 5], wherein: 

SERCOM0 = I2C for IMU nr 1
SERCOM1 = I2C for IMU nr 2
SERCOM2 = I2C for OLED screen
SERCOM3 = SPI for motor control/init
SERCOM3 = USART for general debug 
SERCOM4 = USART for general debug 
SERCOM5 = SPI for TMC4671 debug pins
*/



void enable_sercom_instances(void);
