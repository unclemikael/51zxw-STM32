#include "timer.h"

/* ��ʱ��ֵΪ0 */
__IO uint32_t TimingDelay = 0;

void systick_init()
{
    /* ����Systick����ֵ��ϵͳʱ��Ϊ72MHz */
    /*����72000���ж�ʱ�䣺72000*��1/72000000�� = 1ms*/
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