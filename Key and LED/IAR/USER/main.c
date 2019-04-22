#include "led.h"
#include "timer.h"
#include "key.h"

int main()
{
    u8 led_state = 0;
    SystemInit();
    systick_init();
    led_gpio_init();
    key_gpio_init();
    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
        {
            delay_ms(10);
            if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
            {
                led_state = led_state >= 4 ? 0 : led_state+1;
            }
            while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET);
        }
        
        if((led_state%2) == 1)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_15);
        }else{
            GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        }
      
    }
    
}