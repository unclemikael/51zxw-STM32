#include "timer.h"

/* ��ʱ��ֵΪ0 */
__IO uint32_t TimingDelay = 0;
__IO uint16_t sys_stauts = 0;

void systick_init()
{
    /* ����Ϊ�ⲿ���پ��� 8M*7 */
    RCC_HSEConfig(RCC_HSE_ON);
    while(RCC_WaitForHSEStartUp() != SUCCESS);                  // �ȴ��ⲿ����ʱ�Ӿ�����
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);                                         //ʹ��PLL
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);         //�ȴ�PLL׼������
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                  //����PLLΪϵͳʱ��Դ
    while(RCC_GetSYSCLKSource() != 0x08);                       //�ж�PLL�Ƿ���ϵͳʱ��
    
    /* ����Systick����ֵ��ϵͳʱ��Ϊ72MHz */
    /*����72000���ж�ʱ�䣺72000*��1/72000000�� = 1ms*/
    while(SysTick_Config(72000000/1000) == 1);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    /*ʹ��GPIOB��rccʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  
    
    /*����GPIO����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*��ʼ��GPIO*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void TimingDelay_Decrement()
{
    if(TimingDelay != 0)
    {
        TimingDelay--;
    }
}

void delay_ms(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void system_flash()
{
    if(sys_stauts >= 125)
    {
        sys_stauts = 0;
        
        if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13) != 0)
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
          
        }else{
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }
    }
    sys_stauts++;
}

/* 1ms ����һ�� */
void SysTick_Handler()
{
    TimingDelay_Decrement();
    system_flash();
}