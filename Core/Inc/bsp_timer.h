/*
*********************************************************************************************************
*
*	ģ������ : ��ʱ��ģ��
*	�ļ����� : bsp_timer.h
*	��    �� : V1.3
*	˵    �� : ͷ�ļ�
*
*	Copyright (C), 2015-2016, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

/*
	�ڴ˶������ɸ������ʱ��ȫ�ֱ���
	ע�⣬��������__IO �� volatile����Ϊ����������жϺ���������ͬʱ�����ʣ��п�����ɱ����������Ż���
*/
#define TMR_COUNT	4		/* �����ʱ���ĸ��� ����ʱ��ID��Χ 0 - 3) */

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* һ�ι���ģʽ */
	TMR_AUTO_MODE = 1		/* �Զ���ʱ����ģʽ */
}TMR_MODE_E;

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef struct
{
	volatile unsigned char Mode;		/* ������ģʽ��1���� */
	volatile unsigned char Flag;		/* ��ʱ�����־  */
	volatile unsigned int Count;	/* ������ */
	volatile unsigned int PreLoad;	/* ������Ԥװֵ */
}SOFT_TMR;

/* �ṩ������C�ļ����õĺ��� */
void bsp_InitTimer(void);
void bsp_DelayMS(unsigned int n);
void bsp_DelayUS(unsigned int n);
void bsp_StartTimer(unsigned char _id, unsigned int _period);
void bsp_StartAutoTimer(unsigned char _id, unsigned int _period);
void bsp_StopTimer(unsigned char _id);
unsigned char bsp_CheckTimer(unsigned char _id);
unsigned int bsp_GetRunTime(void);
unsigned int bsp_CheckRunTime(unsigned int _LastTime);

void bsp_InitHardTimer(void);
void bsp_StartHardTimer(unsigned char _CC, unsigned int _uiTimeOut, void * _pCallBack);

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
