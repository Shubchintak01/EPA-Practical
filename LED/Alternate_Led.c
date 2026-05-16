#include <lpc214x.h>

#define LED_MASK 0xFF000000   // LEDs connected from P1.24 to P1.31

void delay(unsigned int time)
{
    unsigned int i, j;

    for(i = 0; i < time; i++)
    {
        for(j = 0; j < 5000; j++);
    }
}

int main(void)
{
    PINSEL2 = 0x00000000;     // Configure Port1 as GPIO
    IODIR1  = LED_MASK;       // Set P1.24 to P1.31 as output

    while(1)
    {
        IOCLR1 = LED_MASK;    // Clear all LEDs
        IOSET1 = 0x55000000;  // Alternate LEDs ON (01010101) EVEN LEDS
        delay(1000);

        IOCLR1 = LED_MASK;    // Clear all LEDs
        IOSET1 = 0xAA000000;  // Opposite alternate LEDs ON (10101010) ODD LEDS
        delay(1000);
    }
}
