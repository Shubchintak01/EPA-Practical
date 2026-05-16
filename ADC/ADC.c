#include "lpc214x.h"
#include "ADC.h"

void ADCInit(void)
{
    PINSEL1 &= 0xF0FFFFFF;   // Configure P0.28 and P0.29 as ADC pins
    PINSEL1 |= 0x05000000;
}

unsigned int ADC_Read(unsigned char channel)
{
    static unsigned int ad1_data;

    // Select channel, CLKDIV, ADC ON
    AD0CR = 0x00200300 | (1 << channel);

    // Start conversion
    AD0CR |= (1 << 24);

    // Wait until conversion complete
    while(!(AD0GDR & 0x80000000));

    // Read ADC result
    ad1_data = (AD0GDR & 0x0000FFC0) >> 6;

    return ad1_data;
}
