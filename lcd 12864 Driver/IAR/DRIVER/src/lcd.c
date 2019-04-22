#include "lcd.h"

/*
#define LCD_BK_ON GPIO_SetBits(GPIOB, GPIO_Pin_2);  //lcd back ground on
#define LCD_BK_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_2);  //lcd back ground on
#define LCD_RST_H GPIO_SetBits(GPIOB, GPIO_Pin_3);  //lcd reset pin high
#define LCD_RST_L GPIO_ResetBits(GPIOB, GPIO_Pin_3);  //lcd reset pin low
#define LCD_A0_H GPIO_SetBits(GPIOB, GPIO_Pin_4);  //lcd A0 pin high
#define LCD_A0_L GPIO_ResetBits(GPIOB, GPIO_Pin_4);  //lcd A0 pin low
#define LCD_CS_H GPIO_SetBits(GPIOB, GPIO_Pin_5);  //lcd CS pin high
#define LCD_CS_L GPIO_ResetBits(GPIOB, GPIO_Pin_5);  //lcd CS pin low
#define LCD_SDI_H GPIO_SetBits(GPIOA, GPIO_Pin_7);  //lcd MOSI pin high
#define LCD_SDI_L GPIO_ResetBits(GPIOA, GPIO_Pin_7);  //lcd MOSI pin low
#define LCD_SCK_H GPIO_SetBits(GPIOA, GPIO_Pin_5);  //lcd SCK pin high
#define LCD_SCK_L GPIO_ResetBits(GPIOA, GPIO_Pin_5);  //lcd SCK pin low
*/


void lcd_gpio_init()
{
    /*禁止使用JTAG引脚，开启复用，当作普通I/O*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}

void write_lcd_data_spi(u8 data)
{
    u8 i, temp_data;
    temp_data = data;
    LCD_CS_H;
    LCD_A0_H;           //写数据
    LCD_SCK_H;          //时钟拉高
    LCD_CS_L;           //片选选定
    for(i=0;i<8;i++)
    {
        LCD_SCK_L;
        if((temp_data & 0x80) == 0x80)
        {
            LCD_SDI_H;
        }else
        {
            LCD_SDI_L;
        }
        LCD_SCK_H;
        temp_data <<= 1;
    }
    LCD_CS_H            //不选定芯片
}

void write_lcd_cmd_spi(u8 cmd)
{
    u8 i, temp_cmd;
    temp_cmd = cmd;
    LCD_CS_H;
    LCD_A0_L;           //写命令
    LCD_SCK_H;          //时钟拉高
    LCD_CS_L;           //片选选定
    for(i=0;i<8;i++)
    {
        LCD_SCK_L;
        if((temp_cmd & 0x80) == 0x80)
        {
            LCD_SDI_H;
        }else
        {
            LCD_SDI_L;
        }
        LCD_SCK_H;
        temp_cmd <<= 1;
    }
    LCD_CS_H            //不选定芯片
}

void lcd_delay(unsigned long value)
{
    u16 i,j;
    for (i=0;i<value;i++)
        for (j=0;j<500;j++);
}

void lcd_HDReset()      //硬重置
{
    LCD_RST_L;
    lcd_delay(2);
    LCD_RST_H;
    lcd_delay(4);
}

void Init_ST7567()
{
    // int i, j;
    lcd_gpio_init();
    
    lcd_delay(10);
    lcd_HDReset();      //复位
    lcd_delay(100);
    
    write_lcd_cmd_spi(0xe2); //Soft rest
    write_lcd_cmd_spi(0xa2); //SET LCD bias(A2-1/9bias; A3-1/7bias)
    write_lcd_cmd_spi(0xa0); //SET ADC NORMAL(OB-POR seg0-00h) A0: NORMAL
                             //A1: REVERSE
    write_lcd_cmd_spi(0xc8); //SET COM OUTPUT SCAN
                             //DIRECTION(0XXXB-NORMAL)-POR COM63-->COM0
    write_lcd_cmd_spi(0xa4); // SET DISPLAY NORMAL (0B-NORMAL)-POR
                             //A4:NORMAL A5:ENTIRE DISPLAY ON
    write_lcd_cmd_spi(0xa6); //SET NORMAL DISPLAY MODE(0B-NORMAL)
                             //A6:NORMAL A7:REVERSE
    write_lcd_cmd_spi(0x25); //SET INTERNAL REGULATOR RESDASTOR
                             //RATIO(100B)-POR
    /* double commamd */                         
    write_lcd_cmd_spi(0x81);
    write_lcd_cmd_spi(0x1a); // SET CONTRAST CONTROL
                             //REGISTER(00,0000H-11,1111H) 30 对比度请修改此值，调浓增大此值，反之调淡。
    
    write_lcd_cmd_spi(0x2f); //SET POWER CONTROL REGISTER (ALL INTERNAL)
    write_lcd_cmd_spi(0x40); //end of initialzation set display start line
    write_lcd_cmd_spi(0xaf); //DisPlay On
    
    /* clean display 
    for(i = 0; i < 8; i++)
    {
        write_lcd_cmd_spi(0xb0+i);
        for(j = 0; j < 128; j++)
        {
            write_lcd_cmd_spi(0x10 + ((j & 0xf0) >> 4));
            write_lcd_cmd_spi(0x00 + (j & 0x0f));
            write_lcd_data_spi(0x00);
        }
    }
    */
}