#include "key.h"
key_state key0, key1, key2, key3;
key_state *keys[] = {&key0, &key1, &key2, &key3};

void key_gpio_init()
{
    /* GPIO�ṹ�� */
    GPIO_InitTypeDef GPIO_InitStructure;
    /*ʹ��GPIOB��rccʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                               //��������
    /* ����GPIO */
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* �����ⲿ�ж��� */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    
    
    /* �ⲿ�жϽṹ�� */
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    /* �����ⲿ�ж� */
    EXTI_Init(&EXTI_InitStructure);
    
    
    /* �����жϿ����� */
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
    /* EXTI 11 �ж� */
    if(EXTI_GetFlagStatus(EXTI_Line11) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line11); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //�ӳ�һ��
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET);
          key0.led_on_off = key0.led_on_off > 4 ? 0 : key0.led_on_off+1;
          key0.key_change_bit = CHGE_IN;                                    //״̬�ı��־
        }
    }
    
    /* EXTI 12 �ж� */
    if(EXTI_GetFlagStatus(EXTI_Line12) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line12); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //�ӳ�һ��
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == RESET);
          key1.led_on_off = key1.led_on_off > 4 ? 0 : key1.led_on_off+1;
          key1.key_change_bit = CHGE_IN;                                    //״̬�ı��־
        }
    }
    
    /* EXTI 13 �ж� */
    if(EXTI_GetFlagStatus(EXTI_Line13) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line13); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //�ӳ�һ��
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == RESET);
          key2.led_on_off = key2.led_on_off > 4 ? 0 : key2.led_on_off+1;
          key2.key_change_bit = CHGE_IN;                                    //״̬�ı��־
        }
    }
    
    /* EXTI 14 �ж� */
    if(EXTI_GetFlagStatus(EXTI_Line14) == SET)
    {
        u16 i,j;
        EXTI_ClearITPendingBit(EXTI_Line14); 
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--); //�ӳ�һ��
        
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == RESET)
        {
          while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == RESET);
          key3.led_on_off = key3.led_on_off > 4 ? 0 : key3.led_on_off+1;
          key3.key_change_bit = CHGE_IN;                                    //״̬�ı��־
        }
    }   
}