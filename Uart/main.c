#include "lpc214x.h"
#include <stdio.h>

// Function declarations
extern void UartInit(unsigned int baudrate);
extern unsigned char UART_GetChar(void);
extern int UART_PutChar(unsigned char ch);

int main(void)
{
    UartInit(9600);   // Initialize UART0

    printf("\r\nThis is a Demonstration for");
    printf("\r\nUART Peripheral for LPC2148");
    printf("\r\nDone on SBC_ARM7 Board\r\n");

    printf("\r\nHit any key on PC keyboard to see result\r\n");

    while (1)
    {
        // Echo received character
        UART_PutChar(UART_GetChar());
    }
}
