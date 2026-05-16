#include <lpc214x.h>

// Segment Definitions
#define SEG_A (1<<16)
#define SEG_B (1<<17)
#define SEG_C (1<<18)
#define SEG_D (1<<19)
#define SEG_E (1<<20)
#define SEG_F (1<<21)
#define SEG_G (1<<22)
#define SEG_DP (1<<23)

// Display Select Pins
#define SEG1 (1<<10)
#define SEG2 (1<<11)

// Digit Patterns (Common Anode)
#define ZERO  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define ONE   (SEG_B | SEG_C)
#define TWO   (SEG_A | SEG_B | SEG_D | SEG_E | SEG_G)
#define THREE (SEG_A | SEG_B | SEG_C | SEG_D | SEG_G)
#define FOUR  (SEG_B | SEG_C | SEG_F | SEG_G)
#define FIVE  (SEG_A | SEG_C | SEG_D | SEG_F | SEG_G)
#define SIX   (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define SEVEN (SEG_A | SEG_B | SEG_C)
#define EIGHT (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define NINE  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)

#define SSEG_MASK (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G|SEG_DP)

// Array for digits
unsigned int seg_data[] =
{
    ZERO, ONE, TWO, THREE, FOUR,
    FIVE, SIX, SEVEN, EIGHT, NINE
};

// Delay Function
void delay(unsigned int time)
{
    unsigned int i,j;

    for(i=0;i<time;i++)
    {
        for(j=0;j<5000;j++);
    }
}

int main()
{
    int i;

    // Configure P0.10 and P0.11 as GPIO
    PINSEL0 &= 0xFF0FFFFF;

    // Configure Port1 as GPIO
    PINSEL2 = 0x00000000;

    // Set directions
    IO0DIR |= (SEG1 | SEG2);
    IO1DIR |= SSEG_MASK;

    // Enable ONLY Display 1
    IO0SET = SEG2;

    // Disable Display 2
    IO0CLR = SEG1;

    while(1)
    {
        for(i=0;i<10;i++)
        {
            // Common Anode: clear segments to ON
            IO1CLR = seg_data[i];

            delay(500);

            // Turn OFF segments
            IO1SET = seg_data[i];
        }
    }
}
