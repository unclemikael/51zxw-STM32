#include "lcd.h"


void lcd_HDReset()      //硬重置
{
    HAL_Delay(10);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);  //LCD_RST_L
    HAL_Delay(2);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);  //LCD_RST_H
    HAL_Delay(100);
}

void write_lcd_data_spi(u8 data)
{
	u8 lcd_data = data;
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);    //不选定芯片
	
	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET);    //写数据
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);    //片选选定
	
    HAL_SPI_Transmit(&hspi1, &lcd_data, 1, 10);
	
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);    //不选定芯片
}

void write_lcd_cmd_spi(u8 cmd)
{
	u8 lcd_cmd = cmd;
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);    //不选定芯片
	
	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET);    //写命令
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);    //片选选定
	
    HAL_SPI_Transmit(&hspi1, &lcd_cmd, 1, 10);
	
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);    //不选定芯片
}

void Init_ST7567()
{
	lcd_HDReset();
	
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
}


void show_num_s(u8 page, u8 colum, u8 number)
{
    u8 i, j;
    u8 col_addr, col_msb, col_lsb;
    
    for(i = 0;i < 1;i++)
    {
        write_lcd_cmd_spi(0xb0 + page + i);         //指向第x+i页
        
        col_addr = colum;
        for(j = 0;j < 6;j++)
        {
          col_msb = 0x10 | ((col_addr >> 4) & 0x0f);
          col_lsb = 0x0f & col_addr;
          
          write_lcd_cmd_spi(col_msb);           //写列地址高4位
          write_lcd_cmd_spi(col_lsb);           //写列地址低4位
          write_lcd_data_spi(num_s[number][i*6 + j]);
          col_addr++;
        }
    }
}

void show_letter_s(u8 page, u8 colum, char letter)
{
    u8 i, j;
    u8 col_addr, col_msb, col_lsb;
    
    u8 number = letter - 'A';
    for(i = 0;i < 1;i++)
    {
        write_lcd_cmd_spi(0xb0 + page + i);         //指向第x+i页
        
        col_addr = colum;
        for(j = 0;j < 6;j++)
        {
          col_msb = 0x10 | ((col_addr >> 4) & 0x0f);
          col_lsb = 0x0f & col_addr;
          
          write_lcd_cmd_spi(col_msb);           //写列地址高4位
          write_lcd_cmd_spi(col_lsb);           //写列地址低4位
          write_lcd_data_spi(letter_s[number][i*6 + j]);
          col_addr++;
        }
    }
}

void show_num_m(u8 page, u8 colum, u8 number)
{
    u8 i, j;
    u8 col_addr, col_msb, col_lsb;
    
    for(i = 0;i < 2;i++)
    {
        write_lcd_cmd_spi(0xb0 + page + i);         //指向第x+i页
        
        col_addr = colum;
        for(j = 0;j < 8;j++)
        {
          col_msb = 0x10 | ((col_addr >> 4) & 0x0f);
          col_lsb = 0x0f & col_addr;
          
          write_lcd_cmd_spi(col_msb);           //写列地址高4位
          write_lcd_cmd_spi(col_lsb);           //写列地址低4位
          write_lcd_data_spi(num_m[number][i*8 + j]);
          col_addr++;
        }
    }
}

void show_letter_m(u8 page, u8 colum, char letter)
{
    u8 i, j;
    u8 col_addr, col_msb, col_lsb;
    
    u8 number = letter - 'A';
    for(i = 0;i < 2;i++)
    {
        write_lcd_cmd_spi(0xb0 + page + i);         //指向第x+i页
        
        col_addr = colum;
        for(j = 0;j < 8;j++)
        {
          col_msb = 0x10 | ((col_addr >> 4) & 0x0f);
          col_lsb = 0x0f & col_addr;
          
          write_lcd_cmd_spi(col_msb);           //写列地址高4位
          write_lcd_cmd_spi(col_lsb);           //写列地址低4位
          write_lcd_data_spi(letter_m[number][i*8 + j]);
          col_addr++;
        }
    }
}

void show_num_l(u8 page, u8 colum, u8 number)
{
    u8 i, j;
    u8 col_addr, col_msb, col_lsb;
    
    for(i = 0;i < 3;i++)
    {
        write_lcd_cmd_spi(0xb0 + page + i);         //指向第x+i页
        
        col_addr = colum;
        for(j = 0;j < 10;j++)
        {
          col_msb = 0x10 | ((col_addr >> 4) & 0x0f);
          col_lsb = 0x0f & col_addr;
          
          write_lcd_cmd_spi(col_msb);           //写列地址高4位
          write_lcd_cmd_spi(col_lsb);           //写列地址低4位
          write_lcd_data_spi(num_l[number][i*10 + j]);
          col_addr++;
        }
    }
}

void show_letter_l(u8 page, u8 colum, char letter)
{
    u8 i, j;
    u8 col_addr, col_msb, col_lsb;
    
    u8 number = letter - 'A';
    for(i = 0;i < 3;i++)
    {
        write_lcd_cmd_spi(0xb0 + page + i);         //指向第x+i页
        
        col_addr = colum;
        for(j = 0;j < 10;j++)
        {
          col_msb = 0x10 | ((col_addr >> 4) & 0x0f);
          col_lsb = 0x0f & col_addr;
          
          write_lcd_cmd_spi(col_msb);           //写列地址高4位
          write_lcd_cmd_spi(col_lsb);           //写列地址低4位
          write_lcd_data_spi(letter_l[number][i*10 + j]);
          col_addr++;
        }
    }
}

void display_num(u8 page, u8 colum, u8 size, u16 num)
{
    u8 i;
    u8 page_temp = page;
    u8 colum_temp = colum;
    u16 num_temp = num;
    
    u8 each_num[4];
    short count = 0;
    
    do
    {
        each_num[count] = num_temp % 10;
        num_temp /= 10;
        count++;
    }while(num_temp > 0);
    
    for(i = 0;i < count;i++)
    {
        switch(size)
        {
            case 1:
                show_num_s(page_temp, colum_temp, each_num[count - 1 - i]);
                colum_temp += 6;
                break;
                
            case 2:
                show_num_m(page_temp, colum_temp, each_num[count - 1 - i]);
                colum_temp += 8;
                break;
                
            case 3:
                show_num_l(page_temp, colum_temp, each_num[count - 1 - i]);
                colum_temp += 10;
                break;
        }
    }
}

void dispaly_string(u8 page, u8 colum, u8 size, u8 *word)
{
    u8 colum_temp, *word_temp;
    
    colum_temp = colum;
    word_temp = word;
    while(*word_temp != '\0')
    {
        switch(size)
        {
            case 1:
            {
                show_letter_s(page, colum_temp, *word_temp);
                colum_temp += 6;
                break;
            }
            case 2:
            {
                show_letter_m(page, colum_temp, *word_temp);
                colum_temp += 8;
                break;
            }
            case 3:
            {
                show_letter_l(page, colum_temp, *word_temp);
                colum_temp += 10;
                break;
            }
            default:
                break;
        }
        word_temp ++;
    }
}

void display_pic(u8 pic_num, u8 pos_or_nec)
{
    u8 i, j;
    u8 col_msb, col_lsb;
    
    for(i = 0; i < 8; i++)
    {
        write_lcd_cmd_spi(0xb0 + i);
        for(j = 0; j < 128; j ++)
        {
            col_msb = ((j >> 4) & 0x0f) | 0x10;
            col_lsb = j & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            if(pos_or_nec == POSTIVE)
            {
                write_lcd_data_spi(logo[pic_num][j + i * 128]);
            }
            else if(pos_or_nec == NECTIVE)
            {
                write_lcd_data_spi(~logo[pic_num][j + i * 128]);
            }
        }
    }
    
}
