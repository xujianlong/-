/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart.h"
#include "USART2.h"
#include "hwjs.h"



void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}


void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}




u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART_RX_STA1=0;       //����״̬���
u16 USART_RX_CNT = 0;
void USART2_IRQHandler(void)                	//����1�жϷ������
{
	uint16_t Res;
	uint16_t num=0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��ͷ)
	{
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������


		if((USART_RX_STA1&0x01)==0x00)//����δ���

		{

			if(USART_RX_STA1&0x02)//���յ���0x2A
			{
				if(Res!=0x23)
				{
					USART_RX_STA1=0;//���մ���,���¿�ʼ
				}

				else
				{
					USART_RX_STA1|=0x01;	//���������

				}

			}
			else //��û�յ�0X2A
			{
				if(Res==0x2A)
				{
					USART_RX_STA1|=0x02;

				}

				else
				{
					USART_RX_BUF[USART_RX_CNT&0X3FFF]=Res ;
					USART_SendData(USART1,Res);
					USART_RX_CNT++;
					if(USART_RX_CNT>(USART_REC_LEN-1))
						USART_RX_STA1=0;//�������ݴ���,���¿�ʼ����
				}
			}
		}

		if(USART_RX_STA1&0x03 == 0x03)
		{
			USART_RX_STA1 = 0;   // ��ձ�־��
			USART_RX_CNT = 0;
			//USART_RX_BUF[USART_RX_CNT]='\0';
			//printf("%d",USART_RX_BUF);
//operate_fun();
		}


	}
}



//u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//u8 USART1_RX_STA1=0;       //����״̬���
//u16 USART1_RX_CNT = 0;
//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	uint16_t Res;
//	uint16_t num=0;
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��ͷ)
//	{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
//		USART_SendData(USART2,Res);
//		if(Res==0x23)
//		{
//			if(USART1_RX_CNT>=USART1_REC_LEN)
//			{
//				USART_RX_CNT=0;
//			}
//			else
//			{

//				USART1_RX_CNT=0;
//				for(uint16_t i=0; i<=USART1_REC_LEN; i++)
//				{
//					USART1_RX_BUF[i]=0;
//				}
//			}
//		}
//		else
//		{
//			USART1_RX_BUF[USART1_RX_CNT]=Res;
//			USART1_RX_CNT++;
//		}
//	}
//}





void EXTI15_10_IRQHandler(void)	  //����ң���ⲿ�ж�
{
	u8 Tim=0,Ok=0,Data,Num=0;

	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)
		{
			Tim=HW_jssj();//��ô˴θߵ�ƽʱ��

			if(Tim>=250) break;//�������õ��ź�

			if(Tim>=200 && Tim<250)
			{
				Ok=1;//�յ���ʼ�ź�
			}
			else if(Tim>=60 && Tim<90)
			{
				Data=1;//�յ����� 1
			}
			else if(Tim>=10 && Tim<50)
			{
				Data=0;//�յ����� 0
			}

			if(Ok==1)
			{
				hw_jsm<<=1;
				hw_jsm+=Data;

				if(Num>=32)
				{
					hw_jsbz=1;
					break;
				}
			}

			Num++;
		}
	}
	Data_Array[0]=(hw_jsm>>24);
	Data_Array[1]=(hw_jsm>>16);
	Data_Array[2]=(hw_jsm>>8);
	Data_Array[3]=(hw_jsm);
	EXTI_ClearITPendingBit(EXTI_Line15);
}






/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
