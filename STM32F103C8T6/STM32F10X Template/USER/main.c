#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
int main()
{
    GPIO_SetBits(GPIOA, 0);
    
    return 0;
}