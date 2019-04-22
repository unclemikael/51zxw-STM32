#ifndef __LED_H_
#define __LED_H_

#include "main.h"


#define LED0_ON(); HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);       //开灯
#define LED0_OFF(); HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);    //关灯

#define LED1_ON(); HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);       //开灯
#define LED1_OFF(); HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);    //关灯

#define LED2_ON(); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);       //开灯
#define LED2_OFF(); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);    //关灯

#define LED3_ON(); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);       //开灯
#define LED3_OFF(); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);    //关灯

void led_gpio_init();

#endif