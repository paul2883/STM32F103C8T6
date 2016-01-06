#include "pwm_output.h"

/*
*函数名：TIM3_PWM_Init
*描述：   TIM3输出pwm信号初始化
*输入：   无
*输出：   无
*/
void TIM4_PWM_Init(void)
{
   TIME4_GPIO_Config();
	 TIME4_Mode_Config();
}

/*
*函数名：TIME3_GPIO_Config
*描述：  配置TIME3复用输出PWM时用到的I/O
*输入：   无
*输出：   无
*/
void TIME4_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/*
*函数名：TIME3_Mode_Config
*描述：   配置tim3输出的pwm信号的模式，如周期、极性、占空比
*输入：   无
*输出：   无
*/
void TIME4_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	/*pwm电平跳变值*/
	u16 CCR1_val=499;
	u16 CCR2_val=374;
  u16 CCR3_val=249;
	u16 CCR4_val=124;

	
  /*
	TIM3CLK=72MHZ Prescaler=0x0 time counter clock =72mhz
	TIM3 ARR Register =999  TIM3 frequency=TIM3 counter clock/(ARR+1)
	TIM3 Channel1 duty cycle=(TIM3_CRR1/TIM3_ARR)*100=50%
	TIM3 Channel2 duty cycle=(TIM3_CRR2/TIM3_ARR)*100=37.5%
	TIM3 Channel3 duty cycle=(TIM3_CRR3/TIM3_ARR)*100=25%
	TIM3 Channel4 duty cycle=(TIM3_CRR4/TIM3_ARR)*100=12.5%
	*/
	TIM_TimeBaseInitStructure.TIM_Period=999; //一个定时周期
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	/* PWM1 mode configuration :channel1*/
  TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //配置为pwm1模式
  TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;// 
  TIM_OCInitStructure.TIM_Pulse=CCR1_val; //设置跳变值，当计数器计数到这个值时，电平发生跳变。
	
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //当定时器计数值小于ccr1_val时为高电平
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);  //使能通道4
  TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable); // 使能TIM4预装载CCR4	
	
	/* PWM1 mode configuration :channel2*/
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR2_val;
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	/* PWM1 mode configuration :channel3*/
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR3_val;
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	/* PWM1 mode configuration :channel4*/
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR4_val;
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	TIM_Cmd(TIM4,ENABLE);
}