#include "usart1.h"


/*
*函数名：USART1_Config
*描述：usart1 gpio配置  工作模式配置  115200  8—N-1
*输入：无
*输出：无
*调用：外部调用
*/
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	
	  /* config USART1 clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
    
	  /*USART1 GPIO config*/
		// TX (PA9)  alternate function push-pull
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9; 
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //复用推挽输出  
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	  // RX(PA10)  input floating
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	  
	  /*USART mode config*/
		USART_InitStructure.USART_BaudRate=115200;
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;
		USART_InitStructure.USART_StopBits=USART_StopBits_1;
		USART_InitStructure.USART_Parity=USART_Parity_No;
		USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_Init(USART1,&USART_InitStructure);
		USART_Cmd(USART1,ENABLE);
		
}


/*
*函数名：UART1_Receive_Interrupt
*描述：串口接收中断
*输入：
*输出：
*调用：外部调用
*/
//void UART1_Receive_Interrupt(void)
//{
//  /*结构体定义*/
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	/*配置RCC时钟*/
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	
//	/*配置nvic*/
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure); //这个必须放在最后！！！！！！！！！！！！！
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	}

//	


