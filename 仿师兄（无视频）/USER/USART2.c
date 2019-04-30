#include "USART2.h"




//�ض���fputc����
int fputc(int ch, FILE *f)
{
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������
	USART2->DR = (u8) ch;
	return ch;
}






//�����ж����ȼ�
void NVIC2_Config(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;

	//���ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannel=DEBUG_USART2_IRQ;

	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;

	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;

	//�ж�ʹ��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;

	//����NVIC��ʼ������
	NVIC_Init(&NVIC_InitStructure);   //ע�ͺ������������ɨ����յ����ݿ���RGB����ע�Ϳ������жϵķ�ʽ����RGB
}

//USART��ʼ������
void USART2_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;


	//������ʱ��
	DEBUG_USART2_APBxClkCmd (DEBUG_USART2_CLK,ENABLE);



	//��ʼ��GPIO�˿�
	//���˿�ʱ��
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK,ENABLE);
	//ѡ���������
	GPIO_InitStructure.GPIO_Pin=DEBUG_USART2_RX_GPIO_PIN;
	//���ý���ģʽΪ��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	//����GPIO��ʼ������
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT,&GPIO_InitStructure);

	//ѡ��������
	GPIO_InitStructure.GPIO_Pin=DEBUG_USART2_TX_GPIO_PIN;
	//���÷���ģʽΪ�������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	//�����ٶ�Ϊ50M
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	//����GPIO��ʼ������,�������
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT,&GPIO_InitStructure);


	//USART����
	//���ò�����115200
	USART_InitStructure.USART_BaudRate=DEBUG_USART2_BAUDRATE;
	//�����ֳ�
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity=USART_Parity_No;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	//���ô��ڳ�ʼ������,�������
	USART_Init(DEBUG_USART2,&USART_InitStructure);


	//�����ж����ȼ�����
	NVIC2_Config();	//ע�ͺ������������ɨ����յ����ݿ���RGB����ע�Ϳ������жϵķ�ʽ����RGB

	//ʹ�ܽ����ж�
	USART_ITConfig(DEBUG_USART2,USART_IT_RXNE, ENABLE);


	//ʹ�ܴ���
	USART_Cmd(DEBUG_USART2,ENABLE);

}

//��д���Ͱ�λ������
void Send2_Byte(USART_TypeDef* PUSARTx, uint8_t Data)
{
	//���ÿ⺯������������
	USART_SendData(PUSARTx,Data);
	//�ж������Ƿ��ͽ���
	while(USART_GetFlagStatus(PUSARTx, USART_FLAG_TXE)==RESET);
}

//����ʮ��λ������
void Send2_HalfWord(USART_TypeDef* PUSARTx, uint16_t Data)
{
	uint8_t tem_h=0,tem_l=0;
	tem_h|=(Data>>8);

	tem_l|=Data;
	//���ÿ⺯������������
	USART_SendData(PUSARTx,tem_h);
	//�ж������Ƿ��ͽ���
	while(USART_GetFlagStatus(PUSARTx, USART_FLAG_TXE)==RESET);

	//���ÿ⺯������������
	USART_SendData(PUSARTx,tem_l);
	//�ж������Ƿ��ͽ���
	while(USART_GetFlagStatus(PUSARTx, USART_FLAG_TXE)==RESET);
}


//���Ͱ�λ����
void Send2_Array(USART_TypeDef* PUSARTx, uint8_t *array,uint8_t num)
{
	uint8_t i;
	for(i=0; i<num; i++)
	{
		Send2_Byte(PUSARTx, array[i]);
	}
	/* �ȴ�������� */
	while(USART_GetFlagStatus(PUSARTx,USART_FLAG_TC)==RESET);
}


//�����ַ���
void Send2_Str(USART_TypeDef* PUSARTx,char* str)
{
	uint16_t i=0;
	do
	{
		Send2_Byte(PUSARTx, *(str+i));
		i++;
	}
	while(*(str+i)!='\0');

	/* �ȴ�������� */
	while(USART_GetFlagStatus(PUSARTx,USART_FLAG_TC)==RESET) {}
}









