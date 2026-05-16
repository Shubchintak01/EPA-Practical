#include <lpc214x.h>

#define LCD_PORT   0x00FF0000
#define EN         (1 << 10)   // Enable pin (P 0.10)
#define RS         (1 << 11)   // Register Select pin (P 0.11)
#define RW         (1 << 20)   // Read/Write pin (P 0.20)
#define LCD_SHIFT  16

// Delay function
void delay(unsigned int time)
{
    int i, j;

    for(i = 0; i < time; i++)
    {
        for(j = 0; j < 100; j++);
    }
}

// Enable pulse
void LCD_strobe()
{
    delay(100);
    IOSET0 = EN;
    delay(100);
    IOCLR0 = EN;
    delay(100);
}

// Function to send data
void LCD_data(unsigned char ch)
{
    IOCLR1 = LCD_PORT;              // Clear data pins
    IOSET1 = (ch << LCD_SHIFT);    // Send data

    IOSET0 = RS;                   // RS = 1 for data
    IOCLR0 = RW;                   // RW = 0 for write

    LCD_strobe();
}

// Function to send command
void LCD_cmd(unsigned char ch)
{
    IOCLR1 = LCD_PORT;             // Clear data pins
    IOSET1 = (ch << LCD_SHIFT);    // Send command

    IOCLR0 = RS;                   // RS = 0 for command
    IOCLR0 = RW;                   // RW = 0 for write

    LCD_strobe();
}

// LCD initialization
void LCD_init(void)
{
    PINSEL0 &= 0xFF0FFFFF;   // P0.10 and P0.11 as GPIO
    PINSEL1 &= 0xFFFFFCFF;   // P0.20 as GPIO
    PINSEL2 &= 0xFFFFFFF3;   // P1.16-P1.23 as GPIO

    IODIR0 |= RS | EN | RW;  // Control pins as output
    IODIR1 |= LCD_PORT;      // Data pins as output

    LCD_cmd(0x38);   // 8-bit mode, 2 lines
    LCD_cmd(0x06);   // Entry mode
    LCD_cmd(0x0C);   // Display ON, cursor OFF
    LCD_cmd(0x01);   // Clear display
    LCD_cmd(0x80);   // Cursor at first line
}

// Display string on LCD
void LCD_display(int row, int pos, unsigned char *ch)
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

    // Display string
    while(*ch)
    {
        LCD_data(*ch++);
    }
}

// Main function
int main()
{
    LCD_init();

    LCD_display(1, 1, "HELLO");
    LCD_display(2, 1, "LPC2148");

    while(1);
}
