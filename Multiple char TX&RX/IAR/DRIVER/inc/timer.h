#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

extern __IO uint32_t TimingDelay;

void systick_init(void);
void delay_ms(__IO uint32_t nTime);
void system_flash();

#endif