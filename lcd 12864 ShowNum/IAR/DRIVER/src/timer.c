#include "timer.h"

/* 延时初值为0 */
__IO uint32_t TimingDelay = 0;
__IO uint16_t sys_stauts = 0;

void systick_init()
{
    /* 设置为外部高速晶振 8M*7 */
    RCC_HSEConfig(RCC_HSE_ON);
    // while(RCC_WaitForHSEStartUp() != SUCCESS);                  // 等待外部高速时钟晶振工作
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);                                         //使能PLL
    // while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);         //等待PLL准备就绪
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                  //设置PLL为系统时钟源
    // while(RCC_GetSYSCLKSource() != 0x08);                       //判断PLL是否是系统时钟
    
    /* 配置Systick重载值，系统时钟为72MHz */
    /*设置72000，中断时间：72000*（1/72000000） = 1ms*/
    while(SysTick_Config(72000000/1000) == 1);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    /*使能GPIOB的rcc时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  
    
    /*配置GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*初始化GPIO*/
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

/* 1ms 进来一次 */
void SysTick_Handler()
{
    TimingDelay_Decrement();
    system_flash();
}