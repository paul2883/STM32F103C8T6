#include "SysTick.h"

/*
*�������� SysTick_Init()
*������   ����ϵͳ�δ�ʱ��
*���룺   ��
*�����   ��
*/
u16 TimingDelay;

void SysTick_Init(void)
{
  if(SysTick_Config(SystemCoreClock/1000000)) //���ó�����1��
	{
	 while(1);
	}
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //ʧ�ܵδ�ʱ����
	
}

/*
*�������� Delay_us()
*������   us��ʱ����
*���룺   ��
*�����   ��
*/
void Delay_us(__IO u32 nTime)
{
	TimingDelay=nTime;
 SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay!=0);
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
  
}
	
	/*
*�������� TimingDelay_Decrement(void)
*������   ��ȡ���ĳ���
*���룺   ��
*�����   ��
*/
void TimingDelay_Decrement(void)
{
  if(TimingDelay_Decrement!=0x0000)
	{
	  TimingDelay--;
	}

}