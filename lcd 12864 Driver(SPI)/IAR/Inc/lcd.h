#ifndef __LCD_H_
#define __LCD_H_

#include "main.h"
#include "spi.h"
#include "gpio.h"

#include "font.h"

#define u8 uint8_t
#define u16 uint16_t

#define POSTIVE 0x01
#define NECTIVE 0x00

void write_lcd_data_spi(u8 data);
void write_lcd_cmd_spi(u8 cmd);
void lcd_HDReset();
void Init_ST7567();

void show_num_s(u8 page, u8 colum, u8 number);
void show_letter_s(u8 page, u8 colum, char letter);
void show_num_m(u8 page, u8 colum, u8 number);
void show_letter_m(u8 page, u8 colum, char letter);
void show_num_l(u8 page, u8 colum, u8 number);
void show_letter_l(u8 page, u8 colum, char letter);
void display_num(u8 page, u8 colum, u8 size, u16 num);
void dispaly_string(u8 page, u8 colum, u8 size, u8 *word);
void display_pic(u8 pic_num, u8 pos_or_nec);

#endif