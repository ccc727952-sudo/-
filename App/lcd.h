#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x.h"
#include "system.h"

/* 控制引脚：DC=PD8  BLK=PD9  RST=PD10  CS=PD11(由MySPI控制) */
#define LCD_DC(x)   (PDout(8)  = (x))
#define LCD_BLK(x)  (PDout(9)  = (x))
#define LCD_RST(x)  (PDout(10) = (x))

#define WHITE           0xFFFF
#define BLACK           0x0000
#define RED             0xF800
#define GREEN           0x07E0
#define BLUE            0x001F
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define CYAN            0x07FF
#define BROWN           0xBC40
#define BRRED           0xFC07
#define GRAY            0x8430
#define DARKBLUE        0x01CF
#define LIGHTBLUE       0x7D7C
#define GRAYBLUE        0x5458
#define LIGHTGREEN      0x841F
#define LGRAY           0xC618
#define LGRAYBLUE       0xA651
#define LBBLUE          0x2B12

void lcd_init(void);
void lcd_hard_reset(void);
void lcd_on(void);
void lcd_off(void);
void lcd_write_cmd(uint8_t cmd);
void lcd_write_data(uint8_t data);
void lcd_write_data16(uint16_t data);
void lcd_write_datan(const uint8_t *data, uint16_t length);
void lcd_set_window(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend);
void lcd_show_dot(uint16_t color);
void lcd_show_line(uint16_t color);
void lcd_clear(uint16_t color);
void lcd_show_picture(const uint8_t *img);

#endif