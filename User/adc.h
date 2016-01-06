#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

#define ADC1_DR ADC1_BASE+0x4c
/*
*函数名：ADC1_Config()
*描述：初始化ADC1
*输入：
*输出：
*调用：外部调用
*/
void ADC1_Config(void);

/*
*函数名：ADC1_GPIO_Config()
*描述:
*输入：
*输出：
*调用：内部调用
*/
static void ADC1_GPIO_Config(void);

/*
*函数名：ADC1_Mode_Config()
*描述：初始化ADC1
*输入：
*输出：
*调用：内部调用
*/
static void ADC1_Mode_Config(void);

#endif