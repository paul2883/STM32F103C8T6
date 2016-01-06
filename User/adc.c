#include "adc.h"

 uint16_t __IO ADC_ConvertedValue;
/*
*��������ADC1_Config()
*��������ʼ��ADC1
*���룺
*�����
*���ã��ⲿ����
*/
void ADC1_Config(void)
{
  ADC1_GPIO_Config();
	ADC1_Mode_Config();
}

/*
*��������ADC1_GPIO_Config()
*����:
*���룺
*�����
*���ã��ⲿ����
*/
static void ADC1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //ʹ��DMAʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��ADC1��GPIOAʱ��
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	}

/*
*��������ADC1_Mode_Config()
*��������ʼ��ADC1
*���룺
*�����
*���ã��ⲿ����
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
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent; //ADC1 �����ڶ���ģʽ��
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;      //��ֹɨ��ģʽ��������ڶ�ͨ���ɼ�
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE; //��������ת��ģʽ������ͣ�ؽ���ADCת��
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None; //��ʹ���ⲿ����ת��
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right; //ʹ���Ҷ���ģʽ
	ADC_InitStructure.ADC_NbrOfChannel=1;             //Ҫת����ͨ����Ŀ
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);  //����ADCʱ�ӣ�ΪPCLK2��8��Ƶ��9MHz APB2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_55Cycles5);//����adc1ͨ��1λ55.5����������
	
	/*ʹ��ADC1 DMA*/
	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	
	
	ADC_ResetCalibration(ADC1); //��λУ׼�Ĵ���
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//����û�в����ⲿ�������������������adcת��ADC1;
	
}