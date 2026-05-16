//Add scroll function and replace main, from this code in normal LCD code

void LCD_scroll_left(unsigned int count)
{
    unsigned int i;

    for(i = 0; i < count; i++)
    {
        LCD_cmd(0x18);      // Shift display left
        // LCD_cmd(0x1C);      // Shift display right
        delay(500);
    }
}

int main(void)
{
    LCD_init();

    LCD_display(1,1,(unsigned char *)"HELLO WORLD LPC2148 LCD");
    while(1)
    {
        LCD_scroll_left(16);
        delay(50);
    }

    return 0;
}