#include "Timer.h"

/***************************************TIM2��ʱ������**********************************************/

/*
 * ��������TIM2_GPIO_Config
 * ����  ������TIM2�����PWM�źŵ�ͨ��
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */

static void TIM4_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM2 clock enable */
	//PCLK1����2��Ƶ����ΪTIM4��ʱ��Դ����36MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/*  GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*****************************PB6���¶��  PB7���Ҷ��*************************/
	/*GPIOA Configuration: TIM4 channel 3 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 * ��������TIM2_Mode_Config
 * ����  ��TIM2 ���PWM�źų�ʼ����ֻҪ�����������
 *         TIM2�Ķ���ͨ���ͻ���PWM�ź����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */

static void TIM4_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* -----------------------------------------------------------------------
	    TIM2 Configuration: generate 2 PWM signals with 2 different duty cycles:
	    TIM2CLK = 36 MHz, Prescaler = 0x0, TIM2 counter clock = 36 MHz
	    TIM2 ARR Register = 999 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
	    TIM2 Frequency = 36 KHz.
	    TIM2 Channel1 duty cycle = (TIM2_CCR1/ TIM2_ARR)* 100 = 50%
	    TIM2 Channel2 duty cycle = (TIM2_CCR2/ TIM2_ARR)* 100 = 37.5%
	    TIM2 Channel3 duty cycle = (TIM2_CCR3/ TIM2_ARR)* 100 = 25%
	    TIM2 Channel4 duty cycle = (TIM2_CCR4/ TIM2_ARR)* 100 = 12.5%
	  ----------------------------------------------------------------------- */

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = (20000-1);       //����ʱ����0������19999����Ϊ20000�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1);	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ36MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse =750;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);	 //ʹ��ͨ��3

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse =750;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);	//ʹ��ͨ��4

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

// TIM_ARRPreloadConfig(TIM2, ENABLE);			 // ʹ��TIM2���ؼĴ���ARR

	/* TIM2 enable counter */
	TIM_Cmd(TIM4, ENABLE);                   //ʹ�ܶ�ʱ��2
}

/*
 * ��������TIM4_PWM_Init
 * ����  ��TIM4��ʼ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void TIM4_PWM_Init(void)
{
	TIM4_GPIO_Config();
	TIM4_Mode_Config();
}
