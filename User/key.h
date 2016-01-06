#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

#define KEY_ON(a)  if(a)\
						GPIO_ResetBits(GPIOA,GPIO_Pin_8);\
            else \
						GPIO_SetBits(GPIOA,GPIO_Pin_8)£»
/*Key configuration function*/
void Key_Config(void);
/*check the key's status*/
void check_key(void);

#endif