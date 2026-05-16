#include <lpc214x.h>
#include <stdio.h>

#include "ADC.h"
#include "ADC_lcd.h"

void delay(unsigned int time)
{
    unsigned int i, j;

    for(i = 0; i < time; i++)
        for(j = 0; j < 5000; j++);
}

int main(void)
{
    unsigned int temp;
    unsigned int mv;

    char line1[16];
    char line2[16];

    LCD_init();

    ADCInit();

    while(1)
    {
        temp = ADC_Read(1);

        // Convert ADC value to mV
        mv = (temp * 3300) / 1023;

        sprintf(line1, "ADC RESULT:");

        sprintf(line2, "%4d mV", mv);

        LCD_display(1, 1, line1);

        LCD_display(2, 1, line2);

        delay(20);
    }
}
