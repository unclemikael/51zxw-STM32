#include "key.h"

void key_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*使能GPIOB的rcc时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}