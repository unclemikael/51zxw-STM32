#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f1xx_hal.h"
#include "tim.h"

#define us_tim htim2

#define delay_ms HAL_Delay


extern __IO uint16_t sys_stauts;
extern __IO int32_t TimingDelay_us;


void delay_us(__IO uint32_t nTime);
void system_flash();


#endif