#include "stm32f10x.h"
#include "led.h"

void main()
{
    led_gpio_init();
    GPIO_SetBits(GPIOB, GPIO_Pin_15);
    while(1);
}