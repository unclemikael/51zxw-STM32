#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define CHGE_IN 1
#define NO_CHGR 0

typedef struct key
{
    u8 led_on_off;
    u8 key_change_bit;
}key_state;
extern key_state key0, key1, key2, key3;

void key_gpio_init();

#endif