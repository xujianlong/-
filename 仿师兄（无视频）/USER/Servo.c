#include "Servo.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"

u8 Angle[8]= {0};
u8 num;


/* ��������SetServoAngle
* ����  ������Ƕȸ�ֵ
* ����  ��servoNum,Angle
* ���  ����
* ����  ���ⲿ����
*/
/*****************����Ƕȸ�ֵ********************/
void SetServoAngle(u16 servoNum,u8 angle)
{
	u16 pwm_value;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(servoNum>2)return;

	if(angle>165)return;//�������Ƕȷ�ֹ����ջ�
	if(angle<1)return;  //������С�Ƕȷ�ֹ����ջ�

	Angle[servoNum-1]=angle;
	pwm_value=2500-(angle*(2000/180));//�Ƕ�ֵת������ֵ

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	                        //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = pwm_value-1;	                       //����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;            //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ

	switch(servoNum)//����л�
	{
	case 1:
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		return;
	case 2:
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		return;
	default:
		return;
	}
}


/*
 * ��������Init_Steer
 * ����  �������ʼ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Init_Steer()
{
	u8 i;
	ee_ReadBytes(Angle,0x10,2);//��eeprom��ȡ�Ƕ�ֵ
	if((Angle[0]==0xff)&&(Angle[1]==0xff))//�����δ������Ƕ�
	{
		for(i=0; i<2; i++)
		{
			Angle[i]=0x5a;//����ֵ90��
		}
		ee_WriteBytes(Angle,0x10,2);//����
	}

	TIM4_PWM_Init();  //TIME4��ʼ��

	for(i=0; i<2; i++)
	{
		SetServoAngle(i+1,Angle[i]);
	}
}
