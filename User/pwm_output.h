#ifndef _PWM_OUTPUT_C
#define _PWM_OUTPUT_C
#include "stm32f10x.h"
/*
*��������TIME3_GPIO_Config
*������  ����TIME3�������PWMʱ�õ���I/O
*���룺   ��
*�����   ��
*/
void TIME4_GPIO_Config(void);

/*
*��������TIME3_Mode_Config
*������   TIM3���pwm�źų�ʼ��
*���룺   ��
*�����   ��
*/
void TIME4_Mode_Config(void);



/*
*��������TIM3_PWM_Init
*������   TIM3���pwm�źų�ʼ��
*���룺   ��
*�����   ��
*/
void TIM4_PWM_Init(void);



#endif