#include "dma.h"

//u8 SendBuff[SENDBUFF_SIZE];


/*
*函数名：DMA_Config
*描述：初始化DMA
*输入：
*输出：
*调用：外部调用
*/
void DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA1时钟
	//NVIC_Config();// 配置DMA中断
	DMA_InitStructure.DMA_PeripheralBaseAddr=USART1_DR_Base;  //外设地址，设置串口数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_ConvertedValue;    //内存地址，要传输变量的指针
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;       //方向，从内存到外设
	DMA_InitStructure.DMA_BufferSize=2;        //传输大小
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址不增
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;   //内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte; //外设数据单位
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //内存数据单位
  DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;              //DMA模式，一次传输
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;      //DMA优先级：中
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;               //禁用内存到内存的传输
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);              //配置DMA1的4通道
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	DMA_Cmd(DMA1_Channel4,ENABLE);                           //使能DMA
	//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);            //配置DMA发送完成后产生中断
} 


/*
*函数名：NVIC_Config()
*描述：初始化NVIC
*输入：
*输出：
*调用：内部调用
*/
static void NVIC_Config(void)  //static 很重要，否则连接时会报错
{
 NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //配置1bit为preemption priority

 NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);	

}
