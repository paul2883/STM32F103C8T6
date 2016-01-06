#include "usart1.h"


/*
*��������USART1_Config
*������usart1 gpio����  ����ģʽ����  115200  8��N-1
*���룺��
*�������
*���ã��ⲿ����
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
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //�����������  
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
*��������UART1_Receive_Interrupt
*���������ڽ����ж�
*���룺
*�����
*���ã��ⲿ����
*/
//void UART1_Receive_Interrupt(void)
//{
//  /*�ṹ�嶨��*/
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	/*����RCCʱ��*/
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	
//	/*����nvic*/
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure); //������������󣡣�����������������������
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	}

//	


