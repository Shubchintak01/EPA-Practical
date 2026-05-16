#ifndef LCD_H
#define LCD_H

void LCD_init(void);
void LCD_cmd(unsigned char ch);
void LCD_data(unsigned char ch);
void LCD_display(int row, int pos, char *ch);

#endif
