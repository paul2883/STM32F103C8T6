#include "exti.h"


/*
*函数名：配置PA15为线终端口，并设置终端优先级
*输入：无
*输出：无
*调用：外部调用
*/

void EXTI_PA15_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	
	/*配置外部线中断PA15时钟，还有AFIO 时钟,EXTI和重映射功能需要开启afio*/
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN|RCC_APB2Periph_GPIOA,ENABLE);
	
	/*Config the NVIC PA15*/
	NVIC_Configuration();
	
	/*EXTI line gpio config PA15*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;  //启用上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*EXTI line PA15 mode config*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

/*
*函数名：NVIC_Configuration
*描述：配置嵌套向量中断控制器NVIC
*输入：无
*输出：无
*调用：内部调用
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	/*设置1bit用来做抢占优先级设置*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
  NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

