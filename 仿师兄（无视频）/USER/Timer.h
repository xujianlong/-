/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/
#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"


void TIM2_PWM_Init(void);
void TIM3_PWM_Init(void);
void TIM5_PWM_Init(void);
void TIM4_Init(void);
void PWM_MOTOR_LEFT(u16 PWM_1);
void PWM_MOTOR_RIGHT(u16 PWM_2);


#endif /* __TIMER_H */
