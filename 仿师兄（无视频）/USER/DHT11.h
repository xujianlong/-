#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"
#include "SysTick.h"
#include "delay.h"

//����IO��ѡ��
#define DHT11_PORT             GPIOG
#define DHT11_CLK              RCC_APB2Periph_GPIOG
#define DHT11_PIN              GPIO_Pin_11

//��ȡIO
#define Read                GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN)


//a=1:����ߵ�ƽ
//a=0:����͵�ƽ
#define OutPut(a)  if(a)\
															      GPIO_SetBits(DHT11_PORT,DHT11_PIN); \
															else \
																		GPIO_ResetBits(DHT11_PORT,DHT11_PIN)


extern void DHT11Read(uint8_t*Data_Array);


#endif /*__DHT11_H*/
