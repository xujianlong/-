#include "SysTick.h"

static __IO u32 TimingDelay;

/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ�� SysTick
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void SysTick_Init(void)
{
	/* SystemCoreClock / 1000    1ms�ж�һ��
	 * SystemCoreClock / 100000	 10us�ж�һ��
	 * SystemCoreClock / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 1000000))
	{
		/* Capture error */
		while (1);
	}
}


/*
 * ��������Delay_us
 * ����  ��us��ʱ����,10usΪһ����λ
 * ����  ��- nTime
 * ���  ����
 * ����  ��Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 10us = 10us
 *       ���ⲿ����
 */

void Delay_us(__IO u32 nTime)//�Ѹ�Ϊus
{
	TimingDelay = nTime;

	while(TimingDelay != 0);
}



/*
 * ��������Delay_ms
 * ����  ��ms��ʱ����
 * ����  ��- nTime
 * ���  ����
 * ����  ��
 *       ���ⲿ����
 */

void Delay_ms(__IO u32 nTime)
{
	TimingDelay = nTime*1000;

	while(TimingDelay != 0);
}


/*
 * ��������Delay_s
 * ����  ������ʱ����
 * ����  ��- nTime
 * ���  ����
 * ����  ��
 *       ���ⲿ����
 */

void Delay_s(__IO u32 nTime)
{
	TimingDelay = nTime*1000000;

	while(TimingDelay != 0);
}



/*
 * ��������TimingDelay_Decrement
 * ����  ����ȡ���ĳ���
 * ����  ����
 * ���  ����
 * ����  ���� SysTick �жϺ��� SysTick_Handler()����
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}


void SysTick_Configuration(void)
{
	/* Setup SysTick Timer for 10 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / 1000000)) //SysTick���ú���
	{
		/* Capture error */
		while (1);
	}
	/* Configure the SysTick handler priority */
	NVIC_SetPriority(SysTick_IRQn, 0x0);//SysTick�ж����ȼ�����
}
