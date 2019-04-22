#include "led.h"
#include "timer.h"
#include "key.h"
#include "usart.h"
extern key_state key0, key1, key2, key3;

int main()
{
    SystemInit();
    systick_init();
    led_gpio_init();
    key_gpio_init();
    usart_init();
    
    
    while(1)
    {
        /* key0 */
        if(key0.key_change_bit == CHGE_IN)
        {
            if(key0.led_on_off % 2)
            {
                LED0_ON();
                USART_SendData(USART1, 1+ '0');
            }else{
                LED0_OFF();
                USART_SendData(USART1, '0');
            }
            key0.key_change_bit = NO_CHGR;
        }
        
        /* key1 */
        if(key1.key_change_bit == CHGE_IN)
        {
            if(key1.led_on_off % 2)
            {
                LED1_ON();
                USART_SendData(USART1, 1+ '0');
            }else{
                LED1_OFF();
                USART_SendData(USART1, '0');
            }
            key1.key_change_bit = NO_CHGR;
        }
        
        /* key2 */
        if(key2.key_change_bit == CHGE_IN)
        {
            if(key2.led_on_off % 2)
            {
                LED2_ON();
                USART_SendData(USART1, 1+ '0');
            }else{
                LED2_OFF();
                USART_SendData(USART1, '0');
            }
            key2.key_change_bit = NO_CHGR;
        }
        
        /* key3 */
        if(key3.key_change_bit == CHGE_IN)
        {
            if(key3.led_on_off % 2)
            {
                LED3_ON();
                USART_SendData(USART1, 1+ '0');
            }else{
                LED3_OFF();
                USART_SendData(USART1, '0');
            }
            key3.key_change_bit = NO_CHGR;
        }
        
    }
}