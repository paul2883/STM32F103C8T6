/********include************/
#include "stm32f10x.h"
#include "led.h"
//#include "key.h"
//#include "exti.h"
#include "usart1.h"
//#include "dma.h"
//#include "adc.h"
#include "SysTick.h"
//#include "pwm_output.h"
//#include "i2c.h"
//#include "MPU6050.h"
#include "stdio.h"
#include "spi.h"
/***************************/


/*******Macro define*//////////

///////////////////////////////

////////////////////////////////
/******Parameter define/reference******///
//extern __IO uint16_t ADC_ConvertedValue; 
//s16 accgyo[7]={0};
///////////////////////////////

////////////////////////////////
/********Function referrence***/
//__IO->volatile
// u32->uint32_t
//void Delay(__IO u32 ncount);
void LED_Config(void);
/*
// 重定向printf
*/

int fputc(int ch,FILE *f);

////////////////////////////////



#ifdef  USE_FULL_ASSERT



/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
   printf("Wrong parameters value: file %s on line %d\r\n", file, line);
	}
}
#endif



/****************main*********************************/
int main()
{
   u8 a[1];
	 u8 rec[1];
	 a[0]=0xff;
	//LED_GPIO_Config();/*LED configuration*/
	USART1_Config();/*USART1 config 115200 8-N-1***/
	//UART1_Receive_Interrupt();/*串口中断配置*/
	//ADC1_Config(); // 配置ADC1，并使用DMA模式
	//DMA_Config();/*DMA配置*/
	SysTick_Init();  //设置为10us中断一次
   // TIM4_PWM_Init();
	
	//USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //串口向DMA发送请求
	//LED(ON);
	//I2C_Config();
//	MPU6050_Initialize();
	//Delay_us(500);
	SPI_Config();
	LED_Config();
	SPI_NRF_MOD_TX();
	//SPI_NRF_MOD_RX();
	 //ErrorStatus b=SPI_NRF_TX_DATAS(a,1);
//   Delay_us(50000);
// u8 b=SPI_NRF_RX_DATAS(rec);
//	 
//	     printf("%x",*rec);
//	

	while(1)
	{
  u8 b=SPI_NRF_TX_DATAS(a,1);
		  Delay_us(500000);
  }
}
/****************************************************/

void LED_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitSructure;
	GPIO_InitSructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitSructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}


void Delay(__IO u32 ncount)
{
  for(;ncount!=0;ncount--);
}

/*
// 重定向printf
*/

int fputc(int ch,FILE *f)
{
 USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	return ch;
}
