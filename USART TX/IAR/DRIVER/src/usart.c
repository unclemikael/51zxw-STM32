#include "usart.h"
#include "key.h"

void usart_init()
{
    /* ��ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA \
                          | RCC_APB2Periph_USART1, ENABLE);
    /* ��ʼ���������� */
    usart_release_gpio_init();
    
    /* �����ж� */
    usart_nvic_config();
    
    /* ���ô���ģʽ */
    usart_config();
    

}

void usart_release_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* ����PA9Ϊ����������� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* ����PA10Ϊ�������� */
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
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //�������պͷ���
    USART_Init(USART1, &USART_InitStructure );
    
    USART_ClearFlag(USART1,USART_FLAG_TC);          //���������ɱ�־λ
    USART_Cmd(USART1, ENABLE);                      //ʹ�ܴ��� 1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //���������ж�
}
/* �ж����������� */
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
                key0.key_change_bit = CHGE_IN;          //״̬�ı��־
                break;
            
            case '1':
                key0.led_on_off = 1;
                key0.key_change_bit = CHGE_IN;          //״̬�ı��־
                break;
            
            case '2':
                key0.led_on_off = key0.led_on_off > 4 ? 0 : key0.led_on_off+1;;
                key0.key_change_bit = CHGE_IN;          //״̬�ı��־
                break;
            default:
                break;
        }
        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
  
  
}