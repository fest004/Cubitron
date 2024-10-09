#include "imu.h"

/*
Drivers for the IMU are fine, except we need to create our own functions for 
SPI communication with our own Microcontroller. We can also look at a new filter
for getting more accurate data, using a complementary filter

Great source for this: https://vanhunteradams.com/Pico/ReactionWheel/Complementary_Filters.html
*/

void imu_init() 
{
    /*
    IMU_INT1_InputEnable(); // Sets the INT1 pin as an input 
    IMU_INT2_InputEnable(); // same but with INT2 pin
    */

    // Write CTRL9_XL = 0x02 to enable proper device configurations
    uint8_t reg = CTRL9_XL;
    uint8_t val = 0x02;
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;

    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */

    reg = CTRL3_C;
    val = 0x01;
    buf[0] = reg;
    buf[1] = val;

    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */

    imu_accel_setup(); // accel needs to be setup first
    imu_gyro_setup();

    /* turn of device configuration register */
    val = 0x00;
    buf[0] = reg;
    buf[1] = val;

    /*
    IMU_SLAVE_SELECT_Clear(); 
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */
}


void imu_gyro_setup() 
{
    // Write INT2_CTRL = ?? -> enables hardware signal on INT2 for new gyro data
    uint8_t reg = INT2_CTRL;
    uint8_t val = 0x02;
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;

    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */

    // gyro LPF1 enable
    reg = CTRL4_C;
    val = 0x02;
    buf[0] = reg;
    buf[1] = val;

    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */

    // high performance mode enable aka start gyro
    // also set the sensitivity to 250dps
    reg = CTRL2_G;
    val = 0x60;
    buf[0] = reg;
    buf[1] = val;
    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */
}


void imu_accel_setup() 
{
    // WriteINT1_CTRL = 0x01 -> enables hardware signal on INT1 for new accel data
    uint8_t reg = INT1_CTRL;
    uint8_t val = 0x01;
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;
   
    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */


    // high performance mode enable aka start accel + low pass filter enable
    // also set the sensitivity to 8g
    reg = CTRL1_XL;
    val = 0x6E;
    buf[0] = reg;
    buf[1] = val;

    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&buf, 2, NULL, 0);
    IMU_SLAVE_SELECT_Set();
    */
}


int imu_WhoAmI(uint8_t* res) 
{
    uint8_t tmp[2] = { 0, 0 };
    uint8_t reg = IMU_READ | WHO_AM_I;

    /*
    IMU_SLAVE_SELECT_Clear();
    SERCOM5_SPI_WriteRead(&reg, 1, tmp, 2);
    IMU_SLAVE_SELECT_Set();
    */

    *res = tmp[1];
    if (tmp[1] == 0x6B) { return 1; }
    return 0;
}


void imu_calibrate_accelerometer(Vec3 *accel, Vec3 *bias, int n_samples)

{
    float sum_x = 0, sum_y = 0, sum_z = 0;
    Vec3 ms2;

    for (int i = 0; i < n_samples; i++) 
    {
        imu_get_accel_ms2(&ms2);
        sum_x += ms2.x;
        sum_y += ms2.y;
        sum_z += ms2.z;
    }
    bias->x = sum_x / n_samples;
    bias->y = sum_y / n_samples;
    bias->z = (sum_z / n_samples) - 9.81;
}


void imu_get_accel_ms2(Vec3* res)
{
    Imu_byte_readings_t readings;
    uint8_t tmp[2] = {0, 0};

    /*
    IMU_SLAVE_SELECT_Clear();
    */

    // Linear acceleration sensor x-axis
    uint8_t reg = 0x28 | IMU_READ; 
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTX_L_A = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    reg = 0x29 | IMU_READ; 
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTX_H_A = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    // Linear acceleration sensor y-axis
    reg = 0x2A | IMU_READ; 
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTY_L_A = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    reg = 0x2B | IMU_READ;
    /*
    SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    */
    readings.OUTY_H_A = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    // Linear acceleration sensor z-axis
    reg = 0x2C | IMU_READ;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTZ_L_A = tmp[1];


    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    reg = 0x2D | IMU_READ;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTZ_H_A = tmp[1];

    int16_t x = (readings.OUTX_H_A << 8) | readings.OUTX_L_A;
    int16_t y = (readings.OUTY_H_A << 8) | readings.OUTY_L_A;
    int16_t z = (readings.OUTZ_H_A << 8) | readings.OUTZ_L_A;
    // needs to be the same sensitivity as the accel setup
    res->x = ((float)x * ACC_SENSITIVITY_FS_8G) * 0.001 * 9.81;
    res->y = ((float)y * ACC_SENSITIVITY_FS_8G) * 0.001 * 9.81;
    res->z = ((float)z * ACC_SENSITIVITY_FS_8G) * 0.001 * 9.81;

    //IMU_SLAVE_SELECT_Set();
}


void imu_get_gyro_rps(Vec3* res)
{
    Imu_byte_readings_t readings;
    uint8_t tmp[2] = {0, 0};

    //IMU_SLAVE_SELECT_Clear();

    // Angular rate sensor pitch axis (x)
    uint8_t reg = IMU_READ | 0x22;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTX_L_G = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    reg = IMU_READ | 0x23;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTX_H_G = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    // Angular rate sensor roll axis (y)
    reg = IMU_READ | 0x24;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTY_L_G = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    reg = IMU_READ | 0x25;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTY_H_G = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    // Angular rate sensor yaw axis (z)
    reg = IMU_READ | 0x26;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTZ_L_G = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    reg = IMU_READ | 0x27;
    //SERCOM5_SPI_WriteRead(&reg, 1, &tmp, 2);
    readings.OUTZ_H_G = tmp[1];

    /*
    IMU_SLAVE_SELECT_Toggle();    
    IMU_SLAVE_SELECT_Toggle();
    */

    // Complete gyro output data for x, y and z channels
    int16_t x = (readings.OUTX_H_G << 8) | readings.OUTX_L_G;
    int16_t y = (readings.OUTY_H_G << 8) | readings.OUTY_L_G;
    int16_t z = (readings.OUTZ_H_G << 8) | readings.OUTZ_L_G;
    // needs to be the same sensitivity as the gyro setup
    res->x = ((float)x * GYRO_SENSITIVITY_FS_250DPS) * 0.001 * 0.0174533;
    res->y = ((float)y * GYRO_SENSITIVITY_FS_250DPS) * 0.001 * 0.0174533;
    res->z = ((float)z * GYRO_SENSITIVITY_FS_250DPS) * 0.001 * 0.0174533;

    //IMU_SLAVE_SELECT_Set();
}

/* *****************************************************************************
 End of File
*/
