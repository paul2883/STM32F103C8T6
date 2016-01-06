#include "i2c.h"

/*
*�������� I2C_Init()
*������   ��ʼ��i2c
*���룺   ��
*�����   ��
*/

void I2C_Config(void)
{
   I2C_GPIO_Config();
	 I2C_Mode_Config();
	
	 
}
/*
*�������� I2C_Mode_Config()
*������   i2cģʽ����
*���룺   ��
*�����   ��
*/
static void I2C_Mode_Config(void)
{
     I2C_InitTypeDef I2C_InitStructure;
	   
		  I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
		 I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
			I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
		 I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
		 I2C_InitStructure.I2C_ClockSpeed=100000;
		 I2C_InitStructure.I2C_OwnAddress1=I2C_OAR2_ADD2;
		  
		 I2C_Init(I2C2,&I2C_InitStructure);
		 I2C_Cmd(I2C2,ENABLE);
}


/*
*�������� I2C_GPIO_Config()
*������   GPIO��������
*���룺   ��
*�����   ��
*/

static void I2C_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
		  
		  /*PB11->SDA PB10->SCL*/
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;// ����Ϊ��©���
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_Init(GPIOB,&GPIO_InitStructure);
}

