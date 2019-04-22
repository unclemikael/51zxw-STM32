#include "led.h"
#include "timer.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "font.h"
#include "dht11.h"

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
    
    //SysTick中断影响lcd输出
    SysTick_Config(0xffff);
    Init_ST7567();
    SysTick_Config(72);
    
    if (dht11_read_data() == 1)
    {
        LED0_ON();
        SysTick_Config(0xffff);
        display_num(0, 2, 1, dht11_buffer[0]);  //湿度
        display_num(2, 2, 1, dht11_buffer[2]);  //温度
    }else
    {
        LED0_OFF();
    }
    
    // display_num(0, 0, 1, 1234);
    // dispaly_string(0, 0, 3, "ABC");
    // display_pic(0, NECTIVE);
    
    while(1)
    {        
        // key_status_check();
        
    }
}