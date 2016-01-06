#include "stm32f10x.h"
#ifndef _SPI_SELF_H
#define _SPI_SELF_H

/*
*�������� SPI_Config
*������   ����SPI1��SPI2
*���룺   ��
*�����   ��
*/
void SPI_Config(void);

/*
*�������� SPI2_Send
*������   SPI2��������
*���룺   ��
*�����   ��
*/
void SPI2_Send(void);

/*
*�������� SPI1_Send
*������   SPI2��������
*���룺   ��
*�����   ��
*/
void SPI1_Send(void);

/*
*�������� SPI2_Rec
*������   SPI2��������
*���룺   ��
*�����   ��
*/
void SPI2_Rec(void);

/*
*�������� SPI1_Rec
*������   SPI1��������
*���룺   ��
*�����   ��
*/
void SPI1_Rec(void);
#endif