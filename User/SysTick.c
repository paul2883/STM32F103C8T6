#include "SysTick.h"

/*
*函数名： SysTick_Init()
*描述：   启动系统滴答定时器
*输入：   无
*输出：   无
*/
u16 TimingDelay;

void SysTick_Init(void)
{
  if(SysTick_Config(SystemCoreClock/1000000)) //调用出错返回1；
	{
	 while(1);
	}
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //失能滴答定时器；
	
}

/*
*函数名： Delay_us()
*描述：   us延时程序
*输入：   无
*输出：   无
*/
void Delay_us(__IO u32 nTime)
{
	TimingDelay=nTime;
 SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay!=0);
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
  
}
	
	/*
*函数名： TimingDelay_Decrement(void)
*描述：   获取节拍程序
*输入：   无
*输出：   无
*/
void TimingDelay_Decrement(void)
{
  if(TimingDelay_Decrement!=0x0000)
	{
	  TimingDelay--;
	}

}