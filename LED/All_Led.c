#include<lpc214x.h>

#define LED_MASK 0XFF000000
#define LED0 24

void delay(unsigned int time){
    unsigned int i, j;
    for(i=0; i<time; i++){
        for(j=0; j<5000; j++);
    }
}

int main(void){
    PINSEL2 = 0;
    IODIR1 = LED_MASK ;

    while(1){
        IODSET1= LED_MASK;
        delay(1500);
        IOCLR1 = LED_MASK;
        delay(1500);
    }
}