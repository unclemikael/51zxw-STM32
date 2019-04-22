#include "led.h"
#include "timer.h"
#include "key.h"

int main()
{
    SystemInit();
    systick_init();
    led_gpio_init();
    key_gpio_init();
    while(1)
    {
        
    }
    
}