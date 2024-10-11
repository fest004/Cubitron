#ifndef IMU_H
#define IMU_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
 
#define IMU_READ            0x80
#define IMU_WRITE           0x00    
#define FUNC_CFG_ACCESS     0x01
#define SLV0_ADD            0x15
#define MASTER_CONFIG       0x14
#define SLV0_SUBADD         0x16
#define SLV0_CONFIG         0x17
#define DATAWRITE_SLV0      0x21
#define SHUB_REG_ACCESS     0x40
#define EXT_SENS_ADDR       0x0C
#define INT1_CTRL           0x0D
#define INT2_CTRL           0x0E
#define CTRL1_XL            0x10
#define CTRL2_G             0x11
#define CTRL9_XL            0x18
#define CTRL4_C             0x13
#define CTRL3_C             0x12
#define WHO_AM_I            0x0F


#define ACC_SENSITIVITY_FS_2G   0.061f
#define ACC_SENSITIVITY_FS_4G   0.122f
#define ACC_SENSITIVITY_FS_8G   0.244f
#define ACC_SENSITIVITY_FS_16G  0.488f

#define GYRO_SENSITIVITY_FS_125DPS    4.375f
#define GYRO_SENSITIVITY_FS_250DPS    8.750f
#define GYRO_SENSITIVITY_FS_500DPS   17.500f
#define GYRO_SENSITIVITY_FS_1000DPS  35.000f
#define GYRO_SENSITIVITY_FS_2000DPS  70.000f
#define GYRO_SENSITIVITY_FS_4000DPS 140.000f



typedef struct
{
    uint8_t OUTX_L_G;       
    uint8_t OUTX_H_G;
    uint8_t OUTY_L_G;  
    uint8_t OUTY_H_G;
    uint8_t OUTZ_L_G;
    uint8_t OUTZ_H_G;
    
    uint8_t OUTX_L_A;
    uint8_t OUTX_H_A;
    uint8_t OUTY_L_A;
    uint8_t OUTY_H_A;
    uint8_t OUTZ_L_A;
    uint8_t OUTZ_H_A;
    
    uint8_t OUTX_L_M;
    uint8_t OUTX_H_M;
    uint8_t OUTY_L_M;
    uint8_t OUTY_H_M;
    uint8_t OUTZ_L_M;
    uint8_t OUTZ_H_M;
    
} Imu_byte_readings_t;

typedef struct
{
	float x;
	float y;
	float z;
} Vec3;


typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} Imu_raw_sensor_data_t;


void imu_init();

void imu_accel_setup();

void imu_gyro_setup();

int imu_WhoAmI(uint8_t* res);

void imu_calibrate_accelerometer(Vec3* accel, Vec3* bias, int samples);

void _imu_read_accel(Imu_raw_sensor_data_t *dev);

void _imu_read_gyro(Imu_raw_sensor_data_t *dev);

void _imu_read_magnet(Imu_raw_sensor_data_t *dev);

void imu_get_accel_ms2(Vec3* res);

void imu_get_accel_g(Vec3* res);

void imu_get_gyro_rps(Vec3* res);

void imu_get_magnet_uT(Vec3* res);



/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* IMU_H */
