#include "timer.h"

/* 延时初值为0 */
__IO uint32_t TimingDelay = 0;

void systick_init()
{
    /* 配置Systick重载值，系统时钟为72MHz */
    /*设置72000，中断时间：72000*（1/72000000） = 1ms*/
    while(SysTick_Config(72000000/1000) == 1);
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

void SysTick_Handler()
{
    TimingDelay_Decrement();
}