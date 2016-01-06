#ifndef _I2C_H
#define _I2C_H

#include "HAL_MPU6050.h"


/*
*�������� I2C_Init()
*������   ��ʼ��i2c
*���룺   ��
*�����   ��
*/

void I2C_Config(void);

/*
*��������MPU6050_Init()
*������   ��ʼ��mpu6050
*���룺   ��
*�����   ��
*/


/*
*�������� I2C_GPIO_Config()
*������   GPIO��������
*���룺   ��
*�����   ��
*/
static void I2C_GPIO_Config(void);
/*
*�������� I2C_Mode_Config()
*������   i2cģʽ����
*���룺   ��
*�����   ��
*/
static void I2C_Mode_Config(void);
#endif 