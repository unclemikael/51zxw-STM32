#ifndef __USART_H_
#define __USART_H_

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void usart_init();
void usart_release_gpio_init();
void usart_config();
void usart_nvic_config();


#endif