#ifndef __DHT11_H_
#define __DHT11_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define DHT11_OUT_H GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define DHT11_OUT_L GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define DHT11_IN GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)

extern u8 dht11_buffer[5];

void dht11_portout();
void dht11_portin();
void dht11_reset();
short dht11_read_bit();
u8 dht11_read_byte();
short dht11_read_data();

#endif