#include "delay.h"

__IO uint16_t sys_stauts = 0;
__IO int32_t TimingDelay_us = 0;


void delay_us(__IO uint32_t nTime)
{
    TimingDelay_us = nTime/5;
    
    __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&us_tim);
    HAL_TIM_Base_Start(&us_tim);    // 开启时钟   
    
    while(TimingDelay_us > 0);
    HAL_TIM_Base_Stop(&us_tim);     //关闭时钟
    HAL_TIM_Base_Stop_IT(&us_tim);
    
}


void system_flash()
{
    if(sys_stauts >= 125)
    {
        sys_stauts = 0;
        
        if(HAL_GPIO_ReadPin(SYS_STATUS_GPIO_Port, SYS_STATUS_Pin) != 0)
        {
            HAL_GPIO_WritePin(SYS_STATUS_GPIO_Port, SYS_STATUS_Pin, GPIO_PIN_RESET);
          
        }else{
            HAL_GPIO_WritePin(SYS_STATUS_GPIO_Port, SYS_STATUS_Pin, GPIO_PIN_SET);
        }
    }
    sys_stauts++;
}


/* US_TIM Interrput */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == us_tim.Instance)
    {
        TimingDelay_us--;        
    }
    
}

/* Systick Interrput */
void HAL_SYSTICK_Callback()
{
    system_flash();
    
}

