#ifndef _I2C_H
#define _I2C_H

#include "HAL_MPU6050.h"


/*
*函数名： I2C_Init()
*描述：   初始化i2c
*输入：   无
*输出：   无
*/

void I2C_Config(void);

/*
*函数名：MPU6050_Init()
*描述：   初始化mpu6050
*输入：   无
*输出：   无
*/


/*
*函数名： I2C_GPIO_Config()
*描述：   GPIO复用配置
*输入：   无
*输出：   无
*/
static void I2C_GPIO_Config(void);
/*
*函数名： I2C_Mode_Config()
*描述：   i2c模式配置
*输入：   无
*输出：   无
*/
static void I2C_Mode_Config(void);
#endif 