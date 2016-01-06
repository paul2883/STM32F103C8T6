#include "key.h"


void Key_Config(void)
{
  GPIO_InitTypeDef GPIO_Initiate;
  GPIO_Initiate.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initiate.GPIO_Pin=GPIO_Pin_15;
	GPIO_Initiate.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initiate);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //not necessary
}

void check_key(void)
{
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15))
						{  GPIO_SetBits(GPIOA,GPIO_Pin_8); }
   else
						{GPIO_ResetBits(GPIOA,GPIO_Pin_8);}
}