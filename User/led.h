#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define ON 0
#define OFF 1
#define LED(a)  if(!a)\
								GPIO_ResetBits(GPIOA,GPIO_Pin_8);\
												else \
								GPIO_SetBits(GPIOA,GPIO_Pin_8);
//�������꣬��������������һ��ʹ��

								
void LED_GPIO_Config(void);
								
#endif /*LEN.H*/