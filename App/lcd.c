#include "lcd.h"
#include "MySPI.h"
#include "systick.h"

#define LCD_BUF_SIZE    15360
#define LCD_WIDTH       240
#define LCD_HEIGHT      320

static uint8_t lcd_buf[LCD_BUF_SIZE];

/* 底层：CS拉低 -> 连续发送 -> CS拉高 */
static void lcd_write_bytes(const uint8_t *data, uint16_t length)
{
    uint16_t i;

    MySPI_Start();
    for (i = 0; i < length; i++)
    {
        MySPI_SwapByte(data[i]);
    }
    MySPI_Stop();
}

void lcd_write_cmd(uint8_t cmd)
{
    LCD_DC(0);
    lcd_write_bytes(&cmd, 1);
}

void lcd_write_data(uint8_t data)
{
    LCD_DC(1);
    lcd_write_bytes(&data, 1);
}

void lcd_write_data16(uint16_t data)
{
    uint8_t databuf[2];

    databuf[0] = data >> 8;
    databuf[1] = data & 0xFF;
    LCD_DC(1);
    lcd_write_bytes(databuf, 2);
}

void lcd_write_datan(const uint8_t *data, uint16_t length)
{
    LCD_DC(1);
    lcd_write_bytes(data, length);
}

void lcd_hard_reset(void)
{
    LCD_RST(0);
    delay_ms(100);
    LCD_RST(1);
    delay_ms(100);
}

void lcd_on(void)
{
    LCD_BLK(1);
    delay_ms(10);
}

void lcd_off(void)
{
    LCD_BLK(0);
    delay_ms(10);
}

void lcd_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    MySPI_Init();                               /* PB3/PB5/PD11 + 关JTAG */

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure);      /* DC / BLK / RST */

    LCD_BLK(0);
    LCD_DC(1);
    LCD_RST(1);

    lcd_hard_reset();
    lcd_on();
    delay_ms(100);

    lcd_write_cmd(0x11);                        /* 退出睡眠 */
    delay_ms(120);

    lcd_write_cmd(0xB2);
    lcd_write_data(0x0C);
    lcd_write_data(0x0C);
    lcd_write_data(0x00);
    lcd_write_data(0x33);
    lcd_write_data(0x33);

    lcd_write_cmd(0x35);
    lcd_write_data(0x00);

    lcd_write_cmd(0x36);
    lcd_write_data(0x00);                       /* 竖屏240x320；若颜色红蓝互换改0x08，若上下颠倒改0xC0 */

    lcd_write_cmd(0x3A);
    lcd_write_data(0x05);                       /* RGB565 */

    lcd_write_cmd(0xB7);
    lcd_write_data(0x35);

    lcd_write_cmd(0xBB);
    lcd_write_data(0x2D);

    lcd_write_cmd(0xC0);
    lcd_write_data(0x2C);

    lcd_write_cmd(0xC2);
    lcd_write_data(0x01);

    lcd_write_cmd(0xC3);
    lcd_write_data(0x15);

    lcd_write_cmd(0xC4);
    lcd_write_data(0x20);

    lcd_write_cmd(0xC6);
    lcd_write_data(0x0F);

    lcd_write_cmd(0xD0);
    lcd_write_data(0xA4);
    lcd_write_data(0xA1);

    lcd_write_cmd(0xD6);
    lcd_write_data(0xA1);

    lcd_write_cmd(0xE0);
    lcd_write_data(0x70);
    lcd_write_data(0x05);
    lcd_write_data(0x0A);
    lcd_write_data(0x0B);
    lcd_write_data(0x0A);
    lcd_write_data(0x27);
    lcd_write_data(0x2F);
    lcd_write_data(0x44);
    lcd_write_data(0x47);
    lcd_write_data(0x37);
    lcd_write_data(0x14);
    lcd_write_data(0x14);
    lcd_write_data(0x29);
    lcd_write_data(0x2F);

    lcd_write_cmd(0xE1);
    lcd_write_data(0x70);
    lcd_write_data(0x07);
    lcd_write_data(0x0C);
    lcd_write_data(0x08);
    lcd_write_data(0x08);
    lcd_write_data(0x04);
    lcd_write_data(0x2F);
    lcd_write_data(0x33);
    lcd_write_data(0x46);
    lcd_write_data(0x18);
    lcd_write_data(0x15);
    lcd_write_data(0x15);
    lcd_write_data(0x2B);
    lcd_write_data(0x2D);

    lcd_write_cmd(0x21);                        /* 反显 */
    lcd_write_cmd(0x29);                        /* 开显示 */
    lcd_write_cmd(0x2C);                        /* 开始写显存 */

    lcd_clear(WHITE);
}

void lcd_set_window(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend)//设置显示窗口
{
    lcd_write_cmd(0x2A);
    lcd_write_data16(xstar);
    lcd_write_data16(xend);

    lcd_write_cmd(0x2B);
    lcd_write_data16(ystar);
    lcd_write_data16(yend);

    lcd_write_cmd(0x2C);
}

void lcd_show_dot(uint16_t color)//显示一个点
{
    lcd_set_window(100, 100, 100, 100);
    lcd_write_data16(color);
}

void lcd_show_line(uint16_t color)//显示一条线
{
    uint16_t i;
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    lcd_set_window(0, 10, LCD_WIDTH - 1, 10);
    for (i = 0; i < LCD_WIDTH; i++)
    {
        lcd_buf[2 * i]     = hi;
        lcd_buf[2 * i + 1] = lo;
    }
    lcd_write_datan(lcd_buf, LCD_WIDTH * 2);    /* 240像素 x 2字节 */
}

void lcd_clear(uint16_t color)//清除屏幕
{
    uint16_t i;
    uint16_t row;
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    lcd_set_window(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    for (i = 0; i < LCD_BUF_SIZE; i += 2)
    {
        lcd_buf[i]     = hi;
        lcd_buf[i + 1] = lo;
    }

    for (row = 0; row < (LCD_WIDTH * LCD_HEIGHT * 2 / LCD_BUF_SIZE); row++)
    {
        lcd_write_datan(lcd_buf, LCD_BUF_SIZE);
    }
}

void lcd_show_picture(const uint8_t *img)//显示一张图片
{
    uint32_t total = LCD_WIDTH * LCD_HEIGHT * 2;
    uint32_t offset;
    uint16_t chunk;

    lcd_set_window(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    for (offset = 0; offset < total; offset += LCD_BUF_SIZE)
    {
        chunk = (uint16_t)((total - offset > LCD_BUF_SIZE) ? LCD_BUF_SIZE : (total - offset));
        lcd_write_datan(img + offset, chunk);
    }
}