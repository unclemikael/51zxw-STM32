#ifndef __DHT11_H_
#define __DHT11_H_

#include "main.h"
#include "delay.h"
#include <stdint.h>

#define u8 uint8_t

#define DHT11_OUT_H HAL_GPIO_WritePin(DHT11_DAT_GPIO_Port, DHT11_DAT_Pin, GPIO_PIN_SET)
#define DHT11_OUT_L HAL_GPIO_WritePin(DHT11_DAT_GPIO_Port, DHT11_DAT_Pin, GPIO_PIN_RESET)
#define DHT11_IN HAL_GPIO_ReadPin(DHT11_DAT_GPIO_Port, DHT11_DAT_Pin)

extern u8 dht11_buffer[5];

void dht11_portout();
void dht11_portin();
void dht11_reset();
short dht11_read_bit();
u8 dht11_read_byte();
short dht11_read_data();

#endif