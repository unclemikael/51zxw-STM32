#include "dht11.h"
#include "timer.h"

u8 dht11_buffer[5];

void dht11_portin()                         //Configure pin as input
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void dht11_portout()                         //Configure pin as output
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void dht11_reset()
{
    dht11_portout();    // 设置成输出模式
    DHT11_OUT_L;         //  MCU拉低总线
    delay_us(19000);       // 保持19ms
    DHT11_OUT_H;         //  MCU拉高总线
    delay_us(30);        // 保持30us
    dht11_portin();
    delay_us(5);
}


short dht11_read_bit()
{
    while(DHT11_IN == RESET);
    delay_us(50);
    if(DHT11_IN == SET)
    {
        while(DHT11_IN == SET);
        return 1;
    }else
    {
        return 0;        
    }
}

u8 dht11_read_byte()
{
    u8 i;
    u8 buffer = 0;
    for(i = 0;i < 8;i++)
    {
        buffer <<= 1;
        buffer |= (u8)dht11_read_bit();
    }
    return buffer;
}

short dht11_read_data()
{
    u8 i;
    u8 butter_and = 0;
    
    dht11_reset();
    if(DHT11_IN == RESET)
    {
        while(DHT11_IN == RESET);
        while(DHT11_IN == SET);
        for(i = 0;i < 4;i++)
        {
            dht11_buffer[i] = dht11_read_byte();
            butter_and += dht11_buffer[i];
        }
        dht11_buffer[4] = dht11_read_byte();
        
        while(DHT11_IN == RESET); 
        dht11_portout();
        DHT11_OUT_H;
        
        if(butter_and == dht11_buffer[4])
          return 1;
        
    }
    
    dht11_portout();
    DHT11_OUT_H;
    
    return 0;
}