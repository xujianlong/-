#include "DHT11.h"


/*
 * �������� static void Input_GPIO_Config(void);
 * ����  : IO�ڽ�������
 * ����  ����
 * ���  : ��
 */
static void Input_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DHT11_CLK,ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//��������
	GPIO_InitStructure.GPIO_Pin=DHT11_PIN;

	GPIO_Init(DHT11_PORT,&GPIO_InitStructure);
}


/*
* �������� static void Output_GPIO_Config(void);
* ����  : IO�ڷ�������
* ����  ����
* ���  : ��
*/
static void Output_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DHT11_CLK,ENABLE);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=DHT11_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(DHT11_PORT,&GPIO_InitStructure);

}


/*
* ��������static void DHT11WriteStart(void);
* ����  : //�����ź�
* ����  ��һά����ָ��
* ���  : ��
*/
static void DHT11WriteStart(void)
{
	//SysTick_Init();
	Output_GPIO_Config();//��IO�����ó����ģʽ
	OutPut(0);
	delay_us(25000);//��ʱ����18ms
	OutPut(1);
	delay_us(3);
}


/*
* ��������static uint8_t Byte_Receive(void);
* ����  : ������8λ���ݽ���
* ����  ����
* ���  : ��
*/
static uint8_t  Byte_Receive(void)
{
	u8 temp=0,i=0,j=0;
	Input_GPIO_Config();
	for(i=0; i<8; i++)
	{
		temp<<=1;
		while(Bit_RESET== Read);//�ȴ���Ϊ�ߵ�ƽ
		while(Read==Bit_SET)//����ߵ�ƽʱ��
		{

			delay_us(1);//��ʱ1us
			j++;
		}
		if(j>=9)        //����30usȷ��Ϊ1
		{
			temp = temp|0x01;
			j=0;
		}
		j=0;

	}
	return temp;

}



/*
* ��������void DHT11Read(uint8_t *Data_Array);
* ����  : �������ݽ��պ���
* ����  ��һά����ָ��
* ���  : ��
*/
void DHT11Read(uint8_t*Data_Array)
{

	uint8_t TH_temp,TL_temp,RH_temp,RL_temp,CK_temp;
	DHT11WriteStart();//��ȡǰ���ź�
	Input_GPIO_Config(); //���ö˿�Ϊ����
	while(Bit_SET==Read);
	if(!Read)
	{
		while(Bit_RESET == Read);//�͵�ƽ��Ӧ�ź�
		while(Bit_SET == Read);//80us�ߵ�ƽ׼���ź�
		RH_temp=Byte_Receive();//ʪ�ȸ�8λ
		RL_temp=Byte_Receive();//ʪ�ȵ�8λ
		TH_temp=Byte_Receive();//�¶ȸ�8λ
		TL_temp=Byte_Receive();//�¶ȵ�8λ
		CK_temp=Byte_Receive();//У���

		Output_GPIO_Config();
		OutPut(1);

		//У��
		if(CK_temp==RH_temp+RL_temp+TH_temp+TL_temp)
		{
			*Data_Array=RH_temp;
			*(Data_Array+1)=RL_temp;
			*(Data_Array+2)=TH_temp;
			*(Data_Array+3)=TL_temp;
			*(Data_Array+4)=CK_temp;
		}

	}
}