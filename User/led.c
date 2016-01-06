#include "led.h"

/*
*函数名： LED_GPIO_Config
*描述：   配置LED用到的I/O口
*输入：   无
*输出：   无
*/

void LED_GPIO_Config(void)
{
  /*定义一个GPIO——InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启GPIO外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	/*选择GPIO引脚的输出模式*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	/*选择GPIO速率*/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  /* 调用库函数，初始化GPIO */
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*关闭LED*/
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	
}