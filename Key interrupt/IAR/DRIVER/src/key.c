#include "key.h"
u8 led_on_off;
void key_gpio_init()
{
    /* GPIO结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;
    /*使能GPIOB的rcc时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    /* 设置GPIO */
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* 连接外部中断线 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
    /* 外部中断结构体 */
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    /* 设置外部中断 */
    EXTI_Init(&EXTI_InitStructure);
    
    
    /* 配置中断控制器 */
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler()
{
    u16 i,j;
    if(EXTI_GetFlagStatus(EXTI_Line11) == SET)
    {
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //延迟一会
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
        {
          led_on_off = led_on_off > 3 ? 0 : led_on_off+1;
        }
        if((led_on_off % 2) == 1)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_15);
        }
        else
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        }
        EXTI_ClearITPendingBit(EXTI_Line11); 
    }
    
}