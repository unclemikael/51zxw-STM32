#include "led.h"

void led_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //ʹ��GPIOB RCCʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    //��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}