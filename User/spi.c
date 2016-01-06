#include "spi.h"
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
/*
*�������� SPI_Config()
*������   ��ʼ��i2c
*���룺   ��
*�����   ��
*/

void SPI_Config(void)
{
  /***GPIO��ʱ������*****/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1|RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //����sck��mosiΪ���츴�����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;// SPI1_SCK->PA5,SPI1_MOSI->PA7,
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//SPI1_CSN->PB1,CE->PB0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����misoΪ��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; //SPI1_MISO->PA6
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4; // IPQ->PA4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//////////////////
	SPI1_CE_LOW();
	SPI1_NRF_CSN_HIGH();
	/****SPI1����*********/
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;// ȫ˫��ģʽ
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;  //��ģʽ
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b; //һ�δ���8bit
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low ;   //���е�ƽΪ�͵�ƽ
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;  //��һ�������ز���

  SPI_InitStructure.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_8; //������Ԥ��Ƶ8  9MHz
  SPI_InitStructure.SPI_NSS=SPI_NSS_Soft; //nss����Ϊ���ģʽ
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;// ���ݴ��������Чλ��ǰ
	SPI_InitStructure.SPI_CRCPolynomial=7;//  CRCУ�鷽ʽ
	SPI_Init(SPI1,&SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE); //ʹ��spi1
	////////
	}

	/*************************************************************
**�������� SPI_RW_Byte(SPI_TypeDef* SPIx,unsigned char Byte);
**����  :   SPIдByte
**����  �� 
**����ֵ�� u8 STATUS�Ĵ���������
**ע��  ��         
************************************************************/
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,unsigned char Byte)
{
      while( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);  //�鷢�ͻ������Ƿ�Ϊ�գ��ռ����Է���
      SPI_I2S_SendData(SPIx, Byte);   //�⺯��������һ���ֽ�
      //��SPI���ջ�����Ϊ��ʱ�ȴ�
      while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
      return SPI_I2S_ReceiveData(SPIx);
}//SPI_RW_Byte()
	
/*************************************************************
**�������� SPI_NRF_Write(char CMD,char* WBuff,char ByteNUM);
**����  :   SPI1дNRF
**����  �� 
**����ֵ�� u8 STATUS
**ע��  ��         
************************************************************/
u8 SPI_NRF_Write(SPI_TypeDef* SPIx,char CMD,unsigned char* WBuff,unsigned char ByteNUM)
{
 unsigned char i,status; 
 SPI1_CE_LOW();  //���ͽ������״̬
 SPI1_NRF_CSN_LOW();//ʹ��Ƭѡ
 
 status=SPI_RW_Byte( SPIx , CMD);
 for(i=0;i<ByteNUM;i++)
 {
     SPI_RW_Byte( SPIx,*WBuff++);
     //printf("д���%d������\r\n",ByteNUM);   
 }
 SPI1_NRF_CSN_HIGH();//
 return status;
}//SPI_NRF_Write()

/*************************************************************
**�������� SPI_NRF_Read(SPI_TypeDef* SPIx,char CMD,char* RBuff,char ByteNUM);
**����  :   SPI1дNRF
**����  �� 
**����ֵ�� u8 status
**ע��  ��         
************************************************************/
u8 SPI_NRF_Read(SPI_TypeDef* SPIx,char CMD,unsigned char* RBuff,unsigned char ByteNUM)
{
 unsigned char i,status ;
  
 SPI1_CE_LOW();
 SPI1_NRF_CSN_LOW(); 
 status=SPI_RW_Byte( SPIx , CMD);
 for(i=0;i< ByteNUM ;i++)
 {    
    RBuff[i]=SPI_RW_Byte(SPIx,NOP);          // ȡ���ջ�������һ���ֽ�
 }
  
 
 SPI1_NRF_CSN_HIGH(); 
 return status; 
}//SPI_NRF_Read()

/*************************************************************
**�������� SPI_NRF_MOD_TX()
**����  :   ����NRF���� ����ģʽ 
**����  ��
**����ֵ�� 
**ע��  ��  �����ڲ��� �޲��޷�  �ɸĳɴ����ò�����ģ�麯��
   Txͨ��0 ��ַTX_ADDR=0x05B6B5B4B3
************************************************************/
void SPI_NRF_MOD_TX(void)
{
	 printf("\r\n Configuring NRF TX Mode....");
  u8 TXRay[7];
	TXRay[0]=0x01;//ʹ��ͨ��0���Զ�Ӧ��    
  TXRay[1]=0x01;//ʹ��ͨ��0�Ľ��ܵ�ַ
  TXRay[2]=0x02; // ��������ͨ��5����
	TXRay[3]=RX_PLOAD_WIDTH; // ѡ��ͨ��0����Ч���ݿ��   
  TXRay[4]=0x0f; //  
  TXRay[5]=0x0e; //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
  
 SPI_NRF_Write(SPI1,W_REG+TX_ADDR,(u8*)TX_ADDRESS,5);//д����շ������ݵĵ�ַ�������ַ�ǽ��ն��ռ���ƾ֤
 SPI_NRF_Write(SPI1,W_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,5); // ����TX�ڵ��ַ,��ҪΪ��ʹ��ACK  
 SPI_NRF_Write(SPI1,W_REG+EN_AA,TXRay,1);//ʹ��ͨ��0���Զ�Ӧ�� 
 SPI_NRF_Write(SPI1,W_REG+EN_RXADDR,TXRay+1,1);//ʹ��ͨ��0�Ľ��յ�ַ
 SPI_NRF_Write(SPI1,W_REG+RF_CH,TXRay+2,1);//����rfͨ��Ƶ��
 //SPI_NRF_Read(SPI1,R_REG+RF_CH,temp,1);
 SPI_NRF_Write(SPI1,W_REG+RX_PW_P0,TXRay+3,1);//ѡ��ͨ��0����Ч���ݿ��    
 //SPI_NRF_Read(SPI1,R_REG+RX_PW_P0,temp,1);
 SPI_NRF_Write(SPI1,W_REG+RF_SETUP,TXRay+4,1);          //����TX�������,0db����,2Mbps,���������濪��   
 SPI_NRF_Write(SPI1,W_REG+CONFIG, TXRay+5,1);           //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
 SPI_NRF_Read(SPI1,R_REG+STATUS,TXRay+6,1);             //������ǰ��״̬�Ĵ���
	SPI_NRF_Write(SPI1,W_REG+STATUS, TXRay+6,1);           //����жϱ�־λ

  SPI1_CE_HIGH();//CE=1 ʹ�ܷ���ģʽ 
 	printf("\r\n TX Configurationg done!");

 Delay_us(10);//CE������Ҫһ������ʱ���ܽ��з��� ��ʱ֮�� ����ͨ��SPI�ӿڷ���TX_PLD
 
}



/*************************************************************
**�������� SPI_NRF_MOD_RX()
**����  :   ����NRF���� ����ģʽ 
**����  ��
**����ֵ�� 
**ע��  ��  �����ڲ��� �޲��޷�  �ɸĳɴ����ò�����ģ�麯��
   RXͨ��0 ��ַTX_ADDR=0xB3B4B5B605
************************************************************/
void SPI_NRF_MOD_RX(void)
{
	 printf("\r\n Configuring NRF RX Mode....");

  u8 TXRay[1];
  

 SPI_NRF_Write(SPI1,W_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,5); // ����TX�ڵ��ַ,��ҪΪ��ʹ��ACK  
 	TXRay[0]=0x01;//ʹ��ͨ��0���Զ�Ӧ��    
  SPI_NRF_Write(SPI1,W_REG+EN_AA,TXRay,1);//ʹ��ͨ��0���Զ�Ӧ�� 
	
	TXRay[0]=0x01;//ʹ��ͨ��0�Ľ��ܵ�ַ
  SPI_NRF_Write(SPI1,W_REG+EN_RXADDR,TXRay,1);//ʹ��ͨ��0�Ľ��յ�ַ
	
	TXRay[0]=0x02; // ��������ͨ��5����
  SPI_NRF_Write(SPI1,W_REG+RF_CH,TXRay,1);//����rfͨ��Ƶ��

	TXRay[0]=RX_PLOAD_WIDTH; // ����rfͨ��Ƶ��
  SPI_NRF_Write(SPI1,W_REG+RX_PW_P0,TXRay,1);//ѡ��ͨ��0����Ч���ݿ��    
  
	TXRay[0]=0x0f; // ѡ��ͨ��0����Ч���ݿ��    
  SPI_NRF_Write(SPI1,W_REG+RF_SETUP,TXRay,1);          //����TX�������,0db����,2Mbps,���������濪��   
   
	TXRay[0]=0x0f; //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ  
  SPI_NRF_Write(SPI1,W_REG+CONFIG, TXRay,1);           //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
  SPI_NRF_Read(SPI1,R_REG+STATUS,TXRay,1);             //������ǰ��״̬�Ĵ���
	SPI_NRF_Write(SPI1,W_REG+STATUS, TXRay,1);           //����жϱ�־λ
  SPI1_CE_HIGH();//CE=1 ʹ�ܷ���ģʽ 
 	printf("\r\n RX Configurationg done!");

 Delay_us(10);//CE������Ҫһ������ʱ���ܽ��з��� ��ʱ֮�� ����ͨ��SPI�ӿڷ���TX_PLD
	
}

/*************************************************************
**�������� SPI_NRF_TX_DATAS()
**����  :   ����NRF���� ����
**����  �� TBuff[ByteNUM] ByteNUM
**����ֵ�� ErrorStatus
**ע��  ��   
************************************************************/
u8 SPI_NRF_TX_DATAS(u8* TBuff,u8 ByteNUM)
{ 
  	printf("\r\n Sending data....");
 
	u8 Status[1];
 {
   SPI1_CE_LOW();//���ʹ���
   SPI_NRF_Write(SPI1,WR_TX_PLOAD,TBuff,ByteNUM);//����TBuff����
   SPI1_CE_HIGH();//���߷���
  }while(NRF_Read_IRQ()!=0);//�жϲ���ʱ��IRQ���ŵ͵�ƽ
 SPI_NRF_Read(SPI1,R_REG+STATUS,Status,1);//��ȡStatus
 SPI_NRF_Write(SPI1,W_REG+STATUS,Status,1); //���TX_DS ��MAX_RT�жϱ�־
	
if(*Status&MAX_TX)//�ﵽ����ط�����
{
  SPI1_CE_LOW();//���ʹ���
  SPI_NRF_Write(SPI1,FLUSH_TX,(u8*)0xff,1);//���TX FIFO�Ĵ��� 
  return MAX_TX; 
}
if(*Status&TX_OK)//�������
{
 return TX_OK;
}

 return 0xff;//����ԭ����ʧ��
 SPI1_CE_LOW();//���ʹ���
 Delay_us(10);
 printf("\r\n Data sent!\r\n");

}
	






/*************************************************************
**�������� SPI_NRF_RX_DATAS()
**����  :   ����NRF���� ����
**����  �� RBuff[ByteNUM] ByteNUM
**����ֵ�� ErrorStatus
**ע��  ��   
************************************************************/
u8 SPI_NRF_RX_DATAS(u8* RBuff)
{
   ErrorStatus RX_Status=SUCCESS;
    u8 Status[1];
 while(NRF_Read_IRQ()!=0);//�жϲ���ʱ��IRQ���ŵ͵�ƽ
 SPI1_CE_LOW();//���ʹ��������ܲ����Ĵ���
 Delay_us(10);
 SPI_NRF_Read(SPI1,R_REG+STATUS,Status,1);//��ȡStatus

 
 SPI_NRF_Read(SPI1,RD_RX_PLOAD,RBuff,4);//��RX_FIFO
 SPI_NRF_Write(SPI1,W_REG+STATUS,Status,1);//����״̬�Ĵ�����־
 printf("data received!\r\n");
	return RX_Status;
}

/*************************************************************
**�������� SPI1_CE_LOW
**����  :  ��CE���õ�
**����  �� 
**����ֵ�� 
**ע��  ��         
************************************************************/
void  SPI1_CE_LOW()
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}

/*************************************************************
**�������� SPI1_CE_HIGH
**����  :  ��CE���ø�
**����  �� 
**����ֵ�� 
**ע��  ��         
************************************************************/
void  SPI1_CE_HIGH()
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
}


/*************************************************************
**�������� SPI1_NRF_CSN_HIGH
**����  :  ����CSNʧ��Ƭѡ
**����  �� 
**����ֵ�� 
**ע��  ��         
************************************************************/
void  SPI1_NRF_CSN_HIGH()
{
  GPIO_SetBits(GPIOB,GPIO_Pin_1);
}

/*************************************************************
**�������� SPI1_NRF_CSN_LOW
**����  :  ����CSNʹ��Ƭѡ
**����  �� 
**����ֵ�� 
**ע��  ��         
************************************************************/
void  SPI1_NRF_CSN_LOW()
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}

/*************************************************************
**��������BitAction NRF_Read_IRQ
**����  :  ��ѯ�Ƿ����ж��ź�
**����  �� 
**����ֵ�� 
**ע��  ��         
************************************************************/
BitAction NRF_Read_IRQ(void)
{
    BitAction IRQ=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
    return IRQ;
}

