#ifndef _PWM_OUTPUT_C
#define _PWM_OUTPUT_C
#include "stm32f10x.h"
/*
*函数名：TIME3_GPIO_Config
*描述：  配置TIME3复用输出PWM时用到的I/O
*输入：   无
*输出：   无
*/
void TIME4_GPIO_Config(void);

/*
*函数名：TIME3_Mode_Config
*描述：   TIM3输出pwm信号初始化
*输入：   无
*输出：   无
*/
void TIME4_Mode_Config(void);



/*
*函数名：TIM3_PWM_Init
*描述：   TIM3输出pwm信号初始化
*输入：   无
*输出：   无
*/
void TIM4_PWM_Init(void);



#endif