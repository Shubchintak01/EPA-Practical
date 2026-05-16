/*
============================================================================
LCD Interface

D0 - P1.16
D1 - P1.17
D2 - P1.18
D3 - P1.19
D4 - P1.20
D5 - P1.21
D6 - P1.22
D7 - P1.23

EN - P0.10
RS - P0.11
RW - P0.20
============================================================================
*/

#include <lpc214x.h>
#include "ADC_lcd.h"

#define LCD_PORT   0x00FF0000
#define EN         (1 << 10)
#define RS         (1 << 11)
#define RW         (1 << 20)
#define LCD_SHIFT  16

void lcd_delay(unsigned int time)
{
    int i, j;

    for(i = 0; i < time; i++)
        for(j = 0; j < 200; j++);
}

void LCD_strobe(void)
{
    lcd_delay(100);

    IOSET0 = EN;

    lcd_delay(100);

    IOCLR0 = EN;

    lcd_delay(100);
}

void LCD_data(unsigned char ch)
{
    IOCLR1 = LCD_PORT;

    IOSET1 = (ch << LCD_SHIFT);

    IOSET0 = RS;

    IOCLR0 = RW;

    LCD_strobe();
}

void LCD_cmd(unsigned char ch)
{
    IOCLR1 = LCD_PORT;

    IOSET1 = (ch << LCD_SHIFT);

    IOCLR0 = RS;

    IOCLR0 = RW;

    LCD_strobe();
}

void LCD_init(void)
{
    PINSEL0 &= 0xFF0FFFFF;   // P0.10 and P0.11 as GPIO
    PINSEL1 &= 0xFFFFFCFF;   // P0.20 as GPIO
    PINSEL2 &= 0xFFFFFFF3;   // Port1 as GPIO

    IODIR0 = RS | EN | RW;

    IODIR1 = LCD_PORT;

    LCD_cmd(0x38);   // 8-bit mode
    LCD_cmd(0x06);   // Entry mode
    LCD_cmd(0x0C);   // Display ON
    LCD_cmd(0x01);   // Clear display
    LCD_cmd(0x80);   // First line
}

void LCD_display(int row, int pos, char *ch)
{
    unsigned char temp;

    if(row == 1)
    {
        temp = 0x80 | (pos - 1);
    }
    else
    {
        temp = 0xC0 | (pos - 1);
    }

    LCD_cmd(temp);

    while(*ch)
    {
        LCD_data(*ch++);
    }
}

