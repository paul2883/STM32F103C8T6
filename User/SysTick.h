#ifndef _SYSTICK_H
#define _SYSTICK_H
#include "stm32f10x.h"

/*
*函数名： SysTick_Init()
*描述：   启动系统滴答定时器
*输入：   无
*输出：   无
*/
void SysTick_Init(void);

/*
*函数名： Delay_us()
*描述：   us延时程序
*输入：   无
*输出：   无
*/
void Delay_us(__IO u32 nTime);

/*
*函数名： TimingDelay_Decrement(void)
*描述：   获取节拍程序
*输入：   无
*输出：   无
*/
void TimingDelay_Decrement(void);


#endif