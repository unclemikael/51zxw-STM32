#include "led.h"
#include "timer.h"
int main()
{
    SystemInit();
    systick_init();
    led_gpio_init();
    while(1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);
        delay_ms(1000);
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        delay_ms(1000);
    }

}