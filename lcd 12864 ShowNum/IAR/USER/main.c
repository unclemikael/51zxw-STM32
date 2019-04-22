#include "led.h"
#include "timer.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"


extern key_state key0, key1, key2, key3;
extern key_state *keys[];

int main()
{
    SystemInit();
    systick_init();
    led_gpio_init();
    key_gpio_init();
    usart_init();
    tx_stack_init();                           //初始化发送缓冲区
    rx_stack_init();                           //初始化接收缓冲区
    Init_ST7567();
    
    show_num(0, 0, 0);
    show_num(0, 0+6+1, 1);
    
    while(1)
    {        
        key_status_check();
        
    }
}