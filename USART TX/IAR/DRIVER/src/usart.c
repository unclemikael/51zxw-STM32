#include "usart.h"
#include "key.h"

void usart_init()
{
    /* 打开时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA \
                          | RCC_APB2Periph_USART1, ENABLE);
    /* 初始化串口引脚 */
    usart_release_gpio_init();
    
    /* 配置中断 */
    usart_nvic_config();
    
    /* 配置串口模式 */
    usart_config();
    

}

void usart_release_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 配置PA9为复用推挽输出 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 配置PA10为浮空输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void usart_config()
{
    USART_InitTypeDef USART_InitStructure;
    
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //1
    USART_InitStructure.USART_Parity = USART_Parity_No;         //n
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件控制
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //开启接收和发送
    USART_Init(USART1, &USART_InitStructure );
    
    USART_ClearFlag(USART1,USART_FLAG_TC);          //清除发送完成标志位
    USART_Cmd(USART1, ENABLE);                      //使能串口 1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //开启传输中断
}
/* 中断向量控制器 */
void usart_nvic_config()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  
}

void USART1_IRQHandler()
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        u16 RxData = USART_ReceiveData(USART1);
        RxData &= 0xff;
        switch(RxData)
        {
            case '0':
                key0.led_on_off = 2;
                key0.key_change_bit = CHGE_IN;          //状态改变标志
                break;
            
            case '1':
                key0.led_on_off = 1;
                key0.key_change_bit = CHGE_IN;          //状态改变标志
                break;
            
            case '2':
                key0.led_on_off = key0.led_on_off > 4 ? 0 : key0.led_on_off+1;;
                key0.key_change_bit = CHGE_IN;          //状态改变标志
                break;
            default:
                break;
        }
        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
  
  
}