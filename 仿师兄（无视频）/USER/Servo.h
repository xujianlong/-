/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/
#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"
#include "timer.h"
void SetServoAngle(u16 servoNum,u8 Angle);
void Init_Steer(void);
void Cruising(void);

#endif /* __SERVO_H */

