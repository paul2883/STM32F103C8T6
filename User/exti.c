#include "exti.h"


/*
*������������PA15Ϊ���ն˿ڣ��������ն����ȼ�
*���룺��
*�������
*���ã��ⲿ����
*/

void EXTI_PA15_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	
	/*�����ⲿ���ж�PA15ʱ�ӣ�����AFIO ʱ��,EXTI����ӳ�书����Ҫ����afio*/
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN|RCC_APB2Periph_GPIOA,ENABLE);
	
	/*Config the NVIC PA15*/
	NVIC_Configuration();
	
	/*EXTI line gpio config PA15*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;  //������������
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
*��������NVIC_Configuration
*����������Ƕ�������жϿ�����NVIC
*���룺��
*�������
*���ã��ڲ�����
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	/*����1bit��������ռ���ȼ�����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
  NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

