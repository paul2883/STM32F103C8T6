#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

#define ADC1_DR ADC1_BASE+0x4c
/*
*��������ADC1_Config()
*��������ʼ��ADC1
*���룺
*�����
*���ã��ⲿ����
*/
void ADC1_Config(void);

/*
*��������ADC1_GPIO_Config()
*����:
*���룺
*�����
*���ã��ڲ�����
*/
static void ADC1_GPIO_Config(void);

/*
*��������ADC1_Mode_Config()
*��������ʼ��ADC1
*���룺
*�����
*���ã��ڲ�����
*/
static void ADC1_Mode_Config(void);

#endif