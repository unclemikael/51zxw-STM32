#include "dht11.h"

u8 dht11_buffer[5];

void dht11_portin()                         //Configure pin as input
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = DHT11_DAT_Pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    
    HAL_GPIO_Init(DHT11_DAT_GPIO_Port, &GPIO_InitStruct);
}

void dht11_portout()                         //Configure pin as output
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = DHT11_DAT_Pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    
    HAL_GPIO_Init(DHT11_DAT_GPIO_Port, &GPIO_InitStruct);
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
    while(DHT11_IN == GPIO_PIN_RESET);
    delay_us(50);
    if(DHT11_IN == GPIO_PIN_SET)
    {
        while(DHT11_IN == GPIO_PIN_SET);
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
    if(DHT11_IN == GPIO_PIN_RESET)
    {
        while(DHT11_IN == GPIO_PIN_RESET);
        while(DHT11_IN == GPIO_PIN_SET);
        for(i = 0;i < 4;i++)
        {
            dht11_buffer[i] = dht11_read_byte();
            butter_and += dht11_buffer[i];
        }
        dht11_buffer[4] = dht11_read_byte();
        
        while(DHT11_IN == GPIO_PIN_RESET); 
        dht11_portout();
        DHT11_OUT_H;
        
        if(butter_and == dht11_buffer[4])
          return 1;
        
    }
    
    dht11_portout();
    DHT11_OUT_H;
    
    return 0;
}