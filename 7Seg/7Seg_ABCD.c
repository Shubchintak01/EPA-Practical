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

#define SSEG_MASK (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G|SEG_DP)

// 7-Segment patterns for alphabets
// (Only possible letters in 7-segment)

#define A (SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define B (SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define C (SEG_A|SEG_D|SEG_E|SEG_F)
#define D (SEG_B|SEG_C|SEG_D|SEG_E|SEG_G)
#define E (SEG_A|SEG_D|SEG_E|SEG_F|SEG_G)
#define F (SEG_A|SEG_E|SEG_F|SEG_G)
#define G (SEG_A|SEG_C|SEG_D|SEG_E|SEG_F)
#define H (SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define I (SEG_B|SEG_C)
#define J (SEG_B|SEG_C|SEG_D|SEG_E)
#define L (SEG_D|SEG_E|SEG_F)
#define N (SEG_C|SEG_E|SEG_G)
#define O (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define P (SEG_A|SEG_B|SEG_E|SEG_F|SEG_G)
#define Q (SEG_A|SEG_B|SEG_C|SEG_F|SEG_G)
#define R (SEG_E|SEG_G)
#define S (SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define T (SEG_D|SEG_E|SEG_F|SEG_G)
#define U (SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define Y (SEG_B|SEG_C|SEG_D|SEG_F|SEG_G)

// Array of displayable alphabets
unsigned int alpha_data[] =
{
    A,B,C,D,E,F,G,H,I,J,
    L,N,O,P,Q,R,S,T,U,Y
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

    // Configure GPIO
    PINSEL0 &= 0xFF0FFFFF;
    PINSEL2 = 0x00000000;

    // Set Directions
    IO0DIR |= (SEG1 | SEG2);
    IO1DIR |= SSEG_MASK;

    // Enable only Display1
    IO0SET = SEG1;
    IO0CLR = SEG2;

    while(1)
    {
        for(i=0;i<20;i++)
        {
            // Common Anode display
            IO1CLR = alpha_data[i];

            delay(500);

            IO1SET = alpha_data[i];
        }
    }
}