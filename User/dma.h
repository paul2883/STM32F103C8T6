#ifndef _DMA_H
#define _DMA_H

#include "stm32f10x.h"
#include "adc.h"

#define USART1_DR_Base 0x40013804
#define SENDBUFF_SIZE 4996

extern __IO u16 ADC_ConvertedValue;
extern u8 a;
/*
*函数名：DMA_Config
*描述：初始化DMA
*输入：
*输出：
*调用：外部调用
*/
void DMA_Config(void);

/*
*函数名：NVIC_Config()
*描述：初始化NVIC
*输入：
*输出：
*调用：内部调用
*/
static void NVIC_Config(void);

#endif