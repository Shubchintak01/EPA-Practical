//LEDs blink in sequence one by one
#include <lpc214x.h>

#define LED_MASK 0xFF000000

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
    unsigned int i;

    PINSEL2 = 0x00000000;      // Configure Port1 as GPIO

    IODIR1 = LED_MASK;         // Set LED pins as output

    while(1)
    {
        for(i = 24; i <= 31; i++)
        {
            IOCLR1 = LED_MASK;     // Turn OFF all LEDs

            IOSET1 = (1 << i);     // Turn ON one LED
            delay(500);
        }
    }
}
