#include <lpc214x.h>

#define STP_MASK 0xF0
unsigned int stepper[] = {0xC0,0x60,0x30,0x90}; //new stepper motor

void delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
    for(j=0;j<5000;j++);

}
int main()
{
    unsigned int i,j;
    PINSEL0 &= ~0x0000FF00;
    IODIR0 |= STP_MASK;
    IOSET0 = STP_MASK;
    while(1)
    {

        for(j=0;j<200;j++) // Clockwise rotation
        {
            for(i=0;i<4;i++)
            {
                IOCLR0 = stepper[i];

                delay(5);
                IOSET0 = STP_MASK;
                delay(5);
            }
        }
        delay(1000);

        for(j=0;j<200;j++) // Anticlockwise rotation
        {
            for(i=0;i<4;i++)
            {
                IOCLR0 = stepper[3-i];
                delay(5);
                IOSET0 = STP_MASK;
                delay(5);
            }
        }
        delay(1000);
    }
}
