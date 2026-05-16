#include "lpc214x.h"
#include <stdio.h>

void UartInit(unsigned int baudrate)   // UART0 initialization
{
    unsigned int FDiv;

    // P0.0 = TxD0 , P0.1 = RxD0
    PINSEL0 &= 0xFFFFFFF0;
    PINSEL0 |= 0x00000005;

    // 8-bit data, 1 stop bit, no parity, DLAB = 1
    U0LCR = 0x83;

    // Baud rate calculation for PCLK = 15MHz
    FDiv = (15000000 / 16) / baudrate;

    U0DLM = FDiv / 256;
    U0DLL = FDiv % 256;

    // DLAB = 0
    U0LCR = 0x03;

    // Enable transmitter
    U0TER = 0x80;
}

unsigned char UART_GetChar(void)
{
    while (!(U0LSR & 0x01));   // Wait until data received
    return U0RBR;
}

int UART_PutChar(unsigned char ch)
{
    while (!(U0LSR & 0x20));   // Wait until THR empty
    U0THR = ch;
    return ch;
}

/* printf support */
struct __FILE
{
    int handle;
};

FILE __stdout;

int fputc(int ch, FILE *f)
{
    return UART_PutChar(ch);
}
