#ifndef _DMA_H
#define _DMA_H

#include "stm32f10x.h"
#include "adc.h"

#define USART1_DR_Base 0x40013804
#define SENDBUFF_SIZE 4996

extern __IO u16 ADC_ConvertedValue;
extern u8 a;
/*
*��������DMA_Config
*��������ʼ��DMA
*���룺
*�����
*���ã��ⲿ����
*/
void DMA_Config(void);

/*
*��������NVIC_Config()
*��������ʼ��NVIC
*���룺
*�����
*���ã��ڲ�����
*/
static void NVIC_Config(void);

#endif