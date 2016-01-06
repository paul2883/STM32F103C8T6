#ifndef _USART1_H
#define _USART1_H

#include "stm32f10x.h"
#include "stdarg.h"

/*
*函数名：USART1_Config
*描述：usart1 gpio配置  工作模式配置  115200  8—N-1
*输入：无
*输出：无
*调用：外部调用
*/
void USART1_Config(void);

/*
*函数名：UART1_Receive_Interrupt
*描述：串口接收中断
*输入：
*输出：
*调用：外部调用
*/
//void UART1_Receive_Interrupt(void);



#endif