#include "dma.h"

//u8 SendBuff[SENDBUFF_SIZE];


/*
*��������DMA_Config
*��������ʼ��DMA
*���룺
*�����
*���ã��ⲿ����
*/
void DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//����DMA1ʱ��
	//NVIC_Config();// ����DMA�ж�
	DMA_InitStructure.DMA_PeripheralBaseAddr=USART1_DR_Base;  //�����ַ�����ô������ݼĴ�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_ConvertedValue;    //�ڴ��ַ��Ҫ���������ָ��
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;       //���򣬴��ڴ浽����
	DMA_InitStructure.DMA_BufferSize=2;        //�����С
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ����
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;   //�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte; //�������ݵ�λ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //�ڴ����ݵ�λ
  DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;              //DMAģʽ��һ�δ���
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;      //DMA���ȼ�����
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;               //�����ڴ浽�ڴ�Ĵ���
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);              //����DMA1��4ͨ��
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	DMA_Cmd(DMA1_Channel4,ENABLE);                           //ʹ��DMA
	//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);            //����DMA������ɺ�����ж�
} 


/*
*��������NVIC_Config()
*��������ʼ��NVIC
*���룺
*�����
*���ã��ڲ�����
*/
static void NVIC_Config(void)  //static ����Ҫ����������ʱ�ᱨ��
{
 NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //����1bitΪpreemption priority

 NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);	

}
