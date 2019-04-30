#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "LED.h"
#include "USART2.h"
#include "adc.h"
#include "function.h"
#include "GENERAL.h"
#include "hwjs.h"
#include "beep.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "SysTick.h"
#include "DHT11.h"
#include "Servo.h"
#include "Timer.h"


uint8_t Data_Array_Dht11[5]= {0};


extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�


u16 adcx;
float temp;
float temp_fan;
u16 temp_int= 0;
u16 temp_first = 0;
u16 temp_second = 0;

uint8_t  window_sta=0,beep_sta=0;

//��ʱ����
void SOFT_DELAY(uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}




/*������������*/
void window_control(void)
{
	if(window_sta!=0)
	{


		AutoControlWindow(temp);
		//printf("%f\n",temp);
//		adcx=Get_Adc_Average(ADC_Channel_0,1);
//			temp=(float)adcx*(3.3/4096);
//			temp_fan=(3.3-(float)adcx*(3.3/4096));
//			temp_int=temp_fan*1000;
//			AutoControlWindow(temp);
//			printf("%f\n",temp);
//			temp_first = temp_int/256;
//			temp_second = temp_int- temp_first*256;

	}

	else
	{

		LED0=1;
		LED1=1;
	}
}
/*��������������*/
void beep_control(void)
{
	if(beep_sta!=0)
	{

		sound1();

	}
}


uint8_t ReadData[256]= {0};
uint8_t I2c_Write[256]= {0,1,2,3,4,5,6,7,8,9};

int main(void)
{
	u8 t=0;
	char sStr [ 100 ] = { 0 },cStr [ 100 ] = { 0 };
	/* ����ϵͳʱ��Ϊ72M */
	SystemInit();
	SysTick_Configuration();  //SysTick�ж����ã���Ҫ������ʱ

	SysTick_Init();


	LED_Init();   //��ʼ��LED
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	USART2_Config();
	Adc_Init();
	GENERAL_TIM_Init();    //��ʼ��PWM
	hwjs_init();   //����ӿڳ�ʼ��
	BEEP_Init();	//�˿ڳ�ʼ��
	Init_Steer();  //������Ƕȳ�ʼ��


	printf("t:%d\n",t);
	USART_SendData(USART2,'2Q');
	USART_SendData(USART1,'e');
	while(1)
	{
		
		printf("�����ܷɳ���:%d\n",t);
		
		
		delay_ms(300);
		
		adcx=Get_Adc_Average(ADC_Channel_0,1);
		temp=(float)adcx*(3.3/4096);
		switch(USART_RX_BUF[0])
		{
		case 0x01:
			switch (USART_RX_BUF[1])
			{
			case 0x0F:
				printf("%d\r\n",0x10);
				window_sta=0x01;



//					AutoControlWindow(temp);
//			printf("%f\n",temp);
				break;
			default :
				window_sta=0x0;
				printf("%d\r\n",0x1f);
				break;

			}
//			adcx=Get_Adc_Average(ADC_Channel_0,1);
//			temp=(float)adcx*(3.3/4096);
//			temp_fan=(3.3-(float)adcx*(3.3/4096));
//			temp_int=temp_fan*1000;
//			AutoControlWindow(temp);
//			printf("%f\n",temp);
//			temp_first = temp_int/256;
//			temp_second = temp_int- temp_first*256;
			break;

		case 0x02:
			SetServoAngle(USART_RX_BUF[1],USART_RX_BUF[3]);
			SetServoAngle(USART_RX_BUF[2],USART_RX_BUF[4]);
			break;

		case 0x03:
			//SOFT_DELAY(0XFFFFFF);
			DHT11Read(Data_Array_Dht11);
			//ǰ��λΪʪ��������С��������λΪ�¶�������С��

			sprintf(sStr,"%d%d%d%d",
			        Data_Array_Dht11[0],Data_Array_Dht11[1],Data_Array_Dht11[2],
			        Data_Array_Dht11[3]);
			printf("%s\r\n",sStr);

//			printf("ʪ��=%d.%d%%RH\r\n�¶�=%d.%d��\r\nУ���=%d\r\n",
//		Data_Array_Dht11[0],Data_Array_Dht11[1],Data_Array_Dht11[2],
//		Data_Array_Dht11[3],Data_Array_Dht11[4]);
			break;

		case 0x04:

			if((USART_RX_BUF[1]!=0)&&(USART_RX_BUF[2]!=0)&&(USART_RX_BUF[3]!=0))
			{
				SET_Color(USART_RX_BUF[1]-1,USART_RX_BUF[2]-1,USART_RX_BUF[3]-1);
			}
			else
			{

				SET_Color(USART_RX_BUF[1],USART_RX_BUF[2],USART_RX_BUF[3]);
			}

			break;

		case 0x05:
//			if(hw_jsbz==1)	//���������յ�
//			{
//				hw_jsbz=0;	   //����
//				printf("��������� %0.8X\r\n",hw_jsm);	//��ӡ
//				printf("��0 %x\r\n��1 %x\r\n��2 %x\r\n��3 %x\r\n",Data_Array[0],Data_Array[1],Data_Array[2],Data_Array[3]);
//				hw_jsm=0;					//����������

//			}
			break;

		case 0x06:
			switch(USART_RX_BUF[1])
			{
			case 0xf0:
				beep_sta=0x01;
				printf("%d\r\n",0x60);
				break;
			default :
				printf("%d\r\n",0x6f);
				beep_sta=0x00;
				break;

			}

			break;

		default :

			break;
		}
		for(uint16_t i=0; i<=USART_REC_LEN; i++)
		{
			USART_RX_BUF[i]=0;
		}


		window_control();
		beep_control();


	}
}



