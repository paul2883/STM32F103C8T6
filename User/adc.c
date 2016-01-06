#include "adc.h"

 uint16_t __IO ADC_ConvertedValue;
/*
*函数名：ADC1_Config()
*描述：初始化ADC1
*输入：
*输出：
*调用：外部调用
*/
void ADC1_Config(void)
{
  ADC1_GPIO_Config();
	ADC1_Mode_Config();
}

/*
*函数名：ADC1_GPIO_Config()
*描述:
*输入：
*输出：
*调用：外部调用
*/
static void ADC1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //使能DMA时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);//使能ADC1和GPIOA时钟
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	}

/*
*函数名：ADC1_Mode_Config()
*描述：初始化ADC1
*输入：
*输出：
*调用：外部调用
*/
static void ADC1_Mode_Config(void)
{
  /****DMA Configuration***/
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR;
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_BufferSize=1;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	///////////////////////////////////
	
	/******ADC1 Configuration****/
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent; //ADC1 工作在独立模式下
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;      //禁止扫描模式，其多用在多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE; //开启连续转换模式，即不停地进行ADC转换
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None; //不使用外部出发转换
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right; //使用右对齐模式
	ADC_InitStructure.ADC_NbrOfChannel=1;             //要转换的通道数目
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);  //配置ADC时钟，为PCLK2的8分频，9MHz APB2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_55Cycles5);//配置adc1通道1位55.5个采样周期
	
	/*使能ADC1 DMA*/
	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	
	
	ADC_ResetCalibration(ADC1); //复位校准寄存器
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//由于没有采用外部触发，所以用软件触发adc转换ADC1;
	
}