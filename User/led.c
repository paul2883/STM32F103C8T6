#include "led.h"

/*
*�������� LED_GPIO_Config
*������   ����LED�õ���I/O��
*���룺   ��
*�����   ��
*/

void LED_GPIO_Config(void)
{
  /*����һ��GPIO����InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*����GPIO����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	/*ѡ��GPIO���ŵ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	/*ѡ��GPIO����*/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  /* ���ÿ⺯������ʼ��GPIO */
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*�ر�LED*/
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	
}