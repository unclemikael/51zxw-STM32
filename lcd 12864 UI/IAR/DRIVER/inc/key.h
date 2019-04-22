#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "led.h"
#include "usart.h"

#define CHGE_IN 1
#define NO_CHGR 0

typedef struct key
{
    u8 led_on_off;
    u8 key_change_bit;
}key_state;
extern key_state key0, key1, key2, key3;
extern key_state *keys[];
extern u8 send_flag;

void key_gpio_init();
void key_status_check();
#endif