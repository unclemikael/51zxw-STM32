#include "led.h"
#include "timer.h"
#include "key.h"
#include "usart.h"
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
    LED0_OFF();
    LED1_OFF();
    LED2_OFF();
    LED3_OFF();
    
    printf("Init");
    
    while(1)
    {
        u8 i;
        u8 send_flag = 0;
        /* keys */
        for(i=0;i<4;i++)
        {
            /* check key status */
            key_state key = *keys[i];
            if(key.key_change_bit == CHGE_IN)
            {
                send_flag = 1;
                if(key.led_on_off % 2)          //OFF -> ON
                {
                    switch(i)
                    {
                        case 0:
                            LED0_ON();
                            tx_stack.data[i] = 0xff;
                            break;
                        case 1:
                            LED1_ON();
                            tx_stack.data[i] = 0xff;
                            break;
                        case 2:
                            LED2_ON();
                            tx_stack.data[i] = 0xff;
                            break;
                        case 3:
                            LED3_ON();
                            tx_stack.data[i] = 0xff;
                            break;
                        default:
                            break;
                      }
                }else                               //ON -> OFF
                {
                    switch(i)
                    {
                        case 0:
                            LED0_OFF();
                            tx_stack.data[i] = 0x00;
                            break;
                        case 1:
                            LED1_OFF();
                            tx_stack.data[i] = 0x00;
                            break;
                        case 2:
                            LED2_OFF();
                            tx_stack.data[i] = 0x00;
                            break;
                        case 3:
                            LED3_OFF();
                            tx_stack.data[i] = 0x00;
                            break;
                        default:
                            break;
                      }
                }
                keys[i]->key_change_bit = NO_CHGR;
            }
        }
        /* TX */
        if(send_flag == 1)
        {
            send_ptl();
            send_flag = 0;
        }
        
        
        /* RX */
        if(rx_stack.lock_flag == LOCK)      //接收完毕
        {
            ptr_handle();            
        }
    }
}