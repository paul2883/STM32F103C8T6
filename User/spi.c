#include "spi.h"
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
/*
*函数名： SPI_Config()
*描述：   初始化i2c
*输入：   无
*输出：   无
*/

void SPI_Config(void)
{
  /***GPIO和时钟配置*****/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1|RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //设置sck，mosi为推挽复用输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;// SPI1_SCK->PA5,SPI1_MOSI->PA7,
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//SPI1_CSN->PB1,CE->PB0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//设置miso为浮空输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; //SPI1_MISO->PA6
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4; // IPQ->PA4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//////////////////
	SPI1_CE_LOW();
	SPI1_NRF_CSN_HIGH();
	/****SPI1配置*********/
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;// 全双工模式
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;  //主模式
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b; //一次传输8bit
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low ;   //空闲电平为低电平
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;  //第一个上升沿采样

  SPI_InitStructure.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_8; //波特率预分频8  9MHz
  SPI_InitStructure.SPI_NSS=SPI_NSS_Soft; //nss管理为软件模式
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;// 数据传输最高有效位在前
	SPI_InitStructure.SPI_CRCPolynomial=7;//  CRC校验方式
	SPI_Init(SPI1,&SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE); //使能spi1
	////////
	}

	/*************************************************************
**函数名： SPI_RW_Byte(SPI_TypeDef* SPIx,unsigned char Byte);
**描述  :   SPI写Byte
**参数  ： 
**返回值： u8 STATUS寄存器的内容
**注意  ：         
************************************************************/
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,unsigned char Byte)
{
      while( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);  //查发送缓冲器是否为空，空即可以发送
      SPI_I2S_SendData(SPIx, Byte);   //库函数：发送一个字节
      //当SPI接收缓冲器为空时等待
      while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
      return SPI_I2S_ReceiveData(SPIx);
}//SPI_RW_Byte()
	
/*************************************************************
**函数名： SPI_NRF_Write(char CMD,char* WBuff,char ByteNUM);
**描述  :   SPI1写NRF
**参数  ： 
**返回值： u8 STATUS
**注意  ：         
************************************************************/
u8 SPI_NRF_Write(SPI_TypeDef* SPIx,char CMD,unsigned char* WBuff,unsigned char ByteNUM)
{
 unsigned char i,status; 
 SPI1_CE_LOW();  //拉低进入待机状态
 SPI1_NRF_CSN_LOW();//使能片选
 
 status=SPI_RW_Byte( SPIx , CMD);
 for(i=0;i<ByteNUM;i++)
 {
     SPI_RW_Byte( SPIx,*WBuff++);
     //printf("写入第%d个数据\r\n",ByteNUM);   
 }
 SPI1_NRF_CSN_HIGH();//
 return status;
}//SPI_NRF_Write()

/*************************************************************
**函数名： SPI_NRF_Read(SPI_TypeDef* SPIx,char CMD,char* RBuff,char ByteNUM);
**描述  :   SPI1写NRF
**参数  ： 
**返回值： u8 status
**注意  ：         
************************************************************/
u8 SPI_NRF_Read(SPI_TypeDef* SPIx,char CMD,unsigned char* RBuff,unsigned char ByteNUM)
{
 unsigned char i,status ;
  
 SPI1_CE_LOW();
 SPI1_NRF_CSN_LOW(); 
 status=SPI_RW_Byte( SPIx , CMD);
 for(i=0;i< ByteNUM ;i++)
 {    
    RBuff[i]=SPI_RW_Byte(SPIx,NOP);          // 取接收缓冲器，一个字节
 }
  
 
 SPI1_NRF_CSN_HIGH(); 
 return status; 
}//SPI_NRF_Read()

/*************************************************************
**函数名： SPI_NRF_MOD_TX()
**描述  :   配置NRF进入 发送模式 
**参数  ：
**返回值： 
**注意  ：  仅用于测试 无参无返  可改成带配置参数的模块函数
   Tx通道0 地址TX_ADDR=0x05B6B5B4B3
************************************************************/
void SPI_NRF_MOD_TX(void)
{
	 printf("\r\n Configuring NRF TX Mode....");
  u8 TXRay[7];
	TXRay[0]=0x01;//使能通道0的自动应答    
  TXRay[1]=0x01;//使能通道0的接受地址
  TXRay[2]=0x02; // 接收数据通道5允许
	TXRay[3]=RX_PLOAD_WIDTH; // 选择通道0的有效数据宽度   
  TXRay[4]=0x0f; //  
  TXRay[5]=0x0e; //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  
 SPI_NRF_Write(SPI1,W_REG+TX_ADDR,(u8*)TX_ADDRESS,5);//写入接收发送数据的地址，这个地址是接收端收件的凭证
 SPI_NRF_Write(SPI1,W_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,5); // 设置TX节点地址,主要为了使能ACK  
 SPI_NRF_Write(SPI1,W_REG+EN_AA,TXRay,1);//使能通道0的自动应答 
 SPI_NRF_Write(SPI1,W_REG+EN_RXADDR,TXRay+1,1);//使能通道0的接收地址
 SPI_NRF_Write(SPI1,W_REG+RF_CH,TXRay+2,1);//设置rf通信频率
 //SPI_NRF_Read(SPI1,R_REG+RF_CH,temp,1);
 SPI_NRF_Write(SPI1,W_REG+RX_PW_P0,TXRay+3,1);//选择通道0的有效数据宽度    
 //SPI_NRF_Read(SPI1,R_REG+RX_PW_P0,temp,1);
 SPI_NRF_Write(SPI1,W_REG+RF_SETUP,TXRay+4,1);          //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
 SPI_NRF_Write(SPI1,W_REG+CONFIG, TXRay+5,1);           //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
 SPI_NRF_Read(SPI1,R_REG+STATUS,TXRay+6,1);             //读出当前的状态寄存器
	SPI_NRF_Write(SPI1,W_REG+STATUS, TXRay+6,1);           //清除中断标志位

  SPI1_CE_HIGH();//CE=1 使能发射模式 
 	printf("\r\n TX Configurationg done!");

 Delay_us(10);//CE拉高需要一定的延时才能进行发送 延时之后 即可通过SPI接口发送TX_PLD
 
}



/*************************************************************
**函数名： SPI_NRF_MOD_RX()
**描述  :   配置NRF进入 发送模式 
**参数  ：
**返回值： 
**注意  ：  仅用于测试 无参无返  可改成带配置参数的模块函数
   RX通道0 地址TX_ADDR=0xB3B4B5B605
************************************************************/
void SPI_NRF_MOD_RX(void)
{
	 printf("\r\n Configuring NRF RX Mode....");

  u8 TXRay[1];
  

 SPI_NRF_Write(SPI1,W_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,5); // 设置TX节点地址,主要为了使能ACK  
 	TXRay[0]=0x01;//使能通道0的自动应答    
  SPI_NRF_Write(SPI1,W_REG+EN_AA,TXRay,1);//使能通道0的自动应答 
	
	TXRay[0]=0x01;//使能通道0的接受地址
  SPI_NRF_Write(SPI1,W_REG+EN_RXADDR,TXRay,1);//使能通道0的接收地址
	
	TXRay[0]=0x02; // 接收数据通道5允许
  SPI_NRF_Write(SPI1,W_REG+RF_CH,TXRay,1);//设置rf通信频率

	TXRay[0]=RX_PLOAD_WIDTH; // 设置rf通信频率
  SPI_NRF_Write(SPI1,W_REG+RX_PW_P0,TXRay,1);//选择通道0的有效数据宽度    
  
	TXRay[0]=0x0f; // 选择通道0的有效数据宽度    
  SPI_NRF_Write(SPI1,W_REG+RF_SETUP,TXRay,1);          //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
   
	TXRay[0]=0x0f; //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式  
  SPI_NRF_Write(SPI1,W_REG+CONFIG, TXRay,1);           //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  SPI_NRF_Read(SPI1,R_REG+STATUS,TXRay,1);             //读出当前的状态寄存器
	SPI_NRF_Write(SPI1,W_REG+STATUS, TXRay,1);           //清除中断标志位
  SPI1_CE_HIGH();//CE=1 使能发射模式 
 	printf("\r\n RX Configurationg done!");

 Delay_us(10);//CE拉高需要一定的延时才能进行发送 延时之后 即可通过SPI接口发送TX_PLD
	
}

/*************************************************************
**函数名： SPI_NRF_TX_DATAS()
**描述  :   配置NRF发送 数据
**参数  ： TBuff[ByteNUM] ByteNUM
**返回值： ErrorStatus
**注意  ：   
************************************************************/
u8 SPI_NRF_TX_DATAS(u8* TBuff,u8 ByteNUM)
{ 
  	printf("\r\n Sending data....");
 
	u8 Status[1];
 {
   SPI1_CE_LOW();//拉低待机
   SPI_NRF_Write(SPI1,WR_TX_PLOAD,TBuff,ByteNUM);//发送TBuff数组
   SPI1_CE_HIGH();//拉高发射
  }while(NRF_Read_IRQ()!=0);//中断产生时，IRQ引脚低电平
 SPI_NRF_Read(SPI1,R_REG+STATUS,Status,1);//读取Status
 SPI_NRF_Write(SPI1,W_REG+STATUS,Status,1); //清除TX_DS 或MAX_RT中断标志
	
if(*Status&MAX_TX)//达到最大重发次数
{
  SPI1_CE_LOW();//拉低待机
  SPI_NRF_Write(SPI1,FLUSH_TX,(u8*)0xff,1);//清除TX FIFO寄存器 
  return MAX_TX; 
}
if(*Status&TX_OK)//发送完成
{
 return TX_OK;
}

 return 0xff;//其他原因发送失败
 SPI1_CE_LOW();//拉低待机
 Delay_us(10);
 printf("\r\n Data sent!\r\n");

}
	






/*************************************************************
**函数名： SPI_NRF_RX_DATAS()
**描述  :   配置NRF发送 数据
**参数  ： RBuff[ByteNUM] ByteNUM
**返回值： ErrorStatus
**注意  ：   
************************************************************/
u8 SPI_NRF_RX_DATAS(u8* RBuff)
{
   ErrorStatus RX_Status=SUCCESS;
    u8 Status[1];
 while(NRF_Read_IRQ()!=0);//中断产生时，IRQ引脚低电平
 SPI1_CE_LOW();//拉低待机，才能操作寄存器
 Delay_us(10);
 SPI_NRF_Read(SPI1,R_REG+STATUS,Status,1);//读取Status

 
 SPI_NRF_Read(SPI1,RD_RX_PLOAD,RBuff,4);//读RX_FIFO
 SPI_NRF_Write(SPI1,W_REG+STATUS,Status,1);//处理状态寄存器标志
 printf("data received!\r\n");
	return RX_Status;
}

/*************************************************************
**函数名： SPI1_CE_LOW
**描述  :  将CE脚置低
**参数  ： 
**返回值： 
**注意  ：         
************************************************************/
void  SPI1_CE_LOW()
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}

/*************************************************************
**函数名： SPI1_CE_HIGH
**描述  :  将CE脚置高
**参数  ： 
**返回值： 
**注意  ：         
************************************************************/
void  SPI1_CE_HIGH()
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
}


/*************************************************************
**函数名： SPI1_NRF_CSN_HIGH
**描述  :  拉高CSN失能片选
**参数  ： 
**返回值： 
**注意  ：         
************************************************************/
void  SPI1_NRF_CSN_HIGH()
{
  GPIO_SetBits(GPIOB,GPIO_Pin_1);
}

/*************************************************************
**函数名： SPI1_NRF_CSN_LOW
**描述  :  拉低CSN使能片选
**参数  ： 
**返回值： 
**注意  ：         
************************************************************/
void  SPI1_NRF_CSN_LOW()
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}

/*************************************************************
**函数名：BitAction NRF_Read_IRQ
**描述  :  查询是否有中断信号
**参数  ： 
**返回值： 
**注意  ：         
************************************************************/
BitAction NRF_Read_IRQ(void)
{
    BitAction IRQ=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
    return IRQ;
}

