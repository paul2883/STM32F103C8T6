#ifndef _SYSTICK_H
#define _SYSTICK_H
#include "stm32f10x.h"

/*
*�������� SysTick_Init()
*������   ����ϵͳ�δ�ʱ��
*���룺   ��
*�����   ��
*/
void SysTick_Init(void);

/*
*�������� Delay_us()
*������   us��ʱ����
*���룺   ��
*�����   ��
*/
void Delay_us(__IO u32 nTime);

/*
*�������� TimingDelay_Decrement(void)
*������   ��ȡ���ĳ���
*���룺   ��
*�����   ��
*/
void TimingDelay_Decrement(void);


#endif