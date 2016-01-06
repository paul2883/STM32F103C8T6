#include "stm32f10x.h"
#ifndef _SPI_SELF_H
#define _SPI_SELF_H

/*
*函数名： SPI_Config
*描述：   配置SPI1和SPI2
*输入：   无
*输出：   无
*/
void SPI_Config(void);

/*
*函数名： SPI2_Send
*描述：   SPI2发送数据
*输入：   无
*输出：   无
*/
void SPI2_Send(void);

/*
*函数名： SPI1_Send
*描述：   SPI2发送数据
*输入：   无
*输出：   无
*/
void SPI1_Send(void);

/*
*函数名： SPI2_Rec
*描述：   SPI2接收数据
*输入：   无
*输出：   无
*/
void SPI2_Rec(void);

/*
*函数名： SPI1_Rec
*描述：   SPI1接收数据
*输入：   无
*输出：   无
*/
void SPI1_Rec(void);
#endif