#include "usart.h"
#include "key.h"

ptl_stack tx_stack;
ptr_stack rx_stack;

void tx_stack_init()
{
    u8 i;
    tx_stack.head = 0xaa;
    tx_stack.direction = 0x09;
    for(i=0;i<4;i++)
    {
        tx_stack.data[i] = 0x00;
    }
    tx_stack.tail = 0xdd;
    usart_init();
}

void rx_stack_init()
{
    u8 i;
    rx_stack.head = 0;
    rx_stack.direction  = 0;
    for(i=0;i<4;i++)
    {
        rx_stack.data[i] = 0;
    }
    rx_stack.data_pt = 0;
    rx_stack.tail = 0;
    rx_stack.lock_flag = UNLOCK;
    usart_init();
}

void send_ptl()
{
    u8 i;
    USART_SendData(USART1, tx_stack.head);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, tx_stack.direction);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    for(i=0;i<4;i++)
    {
        USART_SendData(USART1, tx_stack.data[i]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
    USART_SendData(USART1, tx_stack.tail);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void ptr_handle()
{
    u8 i;
    u8 *stack_pt = &rx_stack.data[0];
    
    for(i=0;i<4;i++)
    {
        keys[i]->key_change_bit = CHGE_IN;
        if(*stack_pt == 0xff)
        {
            if(keys[i]->led_on_off % 2 == 1)
            {
                ;
            }else
            {
                keys[i]->led_on_off = keys[i]->led_on_off >=4 ? 0 : keys[i]->led_on_off + 1;
            }
        }else
        {
            if(keys[i]->led_on_off % 2 == 1)
            {
                keys[i]->led_on_off = keys[i]->led_on_off >=4 ? 0 : keys[i]->led_on_off + 1;
            }else
            {
                ;
            }
        }
        stack_pt++;
    }
    
    rx_stack_init(); 
    // rx_stack.lock_flag = UNLOCK;
}

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


/* interrupt */
void USART1_IRQHandler()
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        u16 RxData = USART_ReceiveData(USART1);
        RxData &= 0x00ff;
        if(rx_stack.lock_flag == UNLOCK)
        {
          switch((u8)RxData)
          {
              case 0xaa:
                  rx_stack.head = 0xaa;
                  break;
              
              case 0xf9:
                  rx_stack.direction = 0xf9;
                  break;
                  
              case 0xdd:
                  rx_stack.tail = 0xdd;
                  break;
               
              default:
                  rx_stack.data[rx_stack.data_pt] = RxData;
                  rx_stack.data_pt = rx_stack.data_pt<=4 ? rx_stack.data_pt+1 : 0;
                  break;
          }
          if((rx_stack.data_pt == 4) && (rx_stack.tail == 0xdd))
          {
              rx_stack.lock_flag = LOCK;
          }
        }
        
        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
  
  
}