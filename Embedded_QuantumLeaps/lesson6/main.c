#include "lm4f120h5qr.h"

/*
#define INTERVAL 1250000

int main()
{
    // for unsigned
  
    unsigned int a = 0x5a5a5a5au;
    unsigned int b = 0xdeadbeefu;
    unsigned int c;
    
    c = a | b;
    c = a & b;
    c = a ^ b; //  exclusive or
    c = ~b;
    c = b << 3;
    // left shift, multiply by 2^3
    c = b >> 1; // rigth shift
    // shifts zeroes into most significant bits
    //devide by 2^1
    // LSRS - logiacal shift
    
    // for signed
    
    int x = 1024;
    int y = -1024;
    int z;
    
    z = x >> 3;
    // zeroes are shifted into the left side
    // ASRS - arithetic shift instruction
    z = y >> 3;
    // sign extending of a negative value in U2 ->
    // ones are shifted into the left side, so the 
    // shift and division relation is preserved
    
    
    SYSCTL_RCGCGPIO_R = 0x20u; //clock gating
    GPIO_PORTF_DIR_R = 0x0eu; // set as outputs (pins 1,2,3)
    GPIO_PORTF_DEN_R = 0x0eu; // digital outputs

    
    while(1) {
        GPIO_PORTF_DATA_R = 0x02u;
        volatile unsigned int counter = 0;
        while (counter < INTERVAL) 
        {
                ++counter;
        }
        GPIO_PORTF_DATA_R = 0x00u;
        counter = 0;
        while (counter < INTERVAL) 
        {
                ++counter;
        }
    }
 
    return 0;
}

*/


#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3) // one shifted 3 places 
#define INTERVAL 1250000

int main()
{
    SYSCTL_RCGCGPIO_R |= (1U << 5); // this, by that i mean |= works if the register is RW!
    GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
  	
    // ((volatile unsigned long *)(0x4005d000))[LED_BLUE] = LED_BLUE; //blue on
    GPIO_PORTF_DATA_R |= LED_BLUE;
    while(1) {
        GPIO_PORTF_DATA_R |= LED_RED;
        unsigned int counter = 0;
        while (counter < INTERVAL) {
                ++counter;
        }
        
        GPIO_PORTF_DATA_R  &= ~LED_RED;
        counter = 0;
        while (counter < INTERVAL) {
                ++counter;
        }

    }
 
    return 0;
}
