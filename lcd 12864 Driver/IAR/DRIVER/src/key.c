#include "key.h"
key_state key0, key1, key2, key3;
key_state *keys[] = {&key0, &key1, &key2, &key3};

u8 send_flag = 0;

void key_gpio_init()
{
    /* GPIO结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;
    /*使能GPIOB的rcc时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                               //上拉输入
    /* 设置GPIO */
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* 连接外部中断线 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    
    
    /* 外部中断结构体 */
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    /* 设置外部中断 */
    EXTI_Init(&EXTI_InitStructure);
    
    
    /* 配置中断控制器 */
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler()
{
    /* EXTI 11 中断 */
    if(EXTI_GetFlagStatus(EXTI_Line11) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line11); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //延迟一会
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET);
          key0.led_on_off = key0.led_on_off > 4 ? 0 : key0.led_on_off+1;
          key0.key_change_bit = CHGE_IN;                                    //状态改变标志
        }
    }
    
    /* EXTI 12 中断 */
    if(EXTI_GetFlagStatus(EXTI_Line12) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line12); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //延迟一会
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == RESET);
          key1.led_on_off = key1.led_on_off > 4 ? 0 : key1.led_on_off+1;
          key1.key_change_bit = CHGE_IN;                                    //状态改变标志
        }
    }
    
    /* EXTI 13 中断 */
    if(EXTI_GetFlagStatus(EXTI_Line13) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line13); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //延迟一会
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == RESET);
          key2.led_on_off = key2.led_on_off > 4 ? 0 : key2.led_on_off+1;
          key2.key_change_bit = CHGE_IN;                                    //状态改变标志
        }
    }
    
    /* EXTI 14 中断 */
    if(EXTI_GetFlagStatus(EXTI_Line14) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line14); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //延迟一会
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == RESET);
          key3.led_on_off = key3.led_on_off > 4 ? 0 : key3.led_on_off+1;
          key3.key_change_bit = CHGE_IN;                                    //状态改变标志
        }
    }   
}


void key_status_check()
{
        u8 i;
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