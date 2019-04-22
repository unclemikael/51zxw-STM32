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
    
    
    write_lcd_cmd_spi(0xb0);
    
    write_lcd_cmd_spi(0x10);
    write_lcd_cmd_spi(0x00);
    write_lcd_data_spi(0x7e);
    
    write_lcd_cmd_spi(0x10);
    write_lcd_cmd_spi(0x01);
    write_lcd_data_spi(0x81);
    
    write_lcd_cmd_spi(0x10);
    write_lcd_cmd_spi(0x02);
    write_lcd_data_spi(0x81);
    
    write_lcd_cmd_spi(0x10);
    write_lcd_cmd_spi(0x03);
    write_lcd_data_spi(0x81);
    
    write_lcd_cmd_spi(0x10);
    write_lcd_cmd_spi(0x04);
    write_lcd_data_spi(0x7e);
    
    while(1)
    {        
        key_status_check();
        
    }
}