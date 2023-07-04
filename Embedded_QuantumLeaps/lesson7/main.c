#include "lm4f120h5qr.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)


#define INTERVAL 1250000

int main()
{
  
    SYSCTL_RCGCGPIO_R |= (1U << 5); // this, by that i mean |= works if the register is RW!
  
    SYSCTL_GPIOHBCTL_R |= (1u << 5); // enable the AHB for gpio port f
    
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
  
    
    
    
    // the << 2 shift because the lst two adress lines are unused
    //*((unsigned long volatile*)(0x40025000u + (LED_BLUE << 2))) = 0xffffffff;
    
    // GPIO_PORTF_DATA_R |= LED_BLUE;
    
    // ((volatile unsigned long *)(0x40025000u))[LED_BLUE] = LED_BLUE; //blue on
    //
    // *((unsigned long volatile*)(0x40025000u + (LED_GREEN << 2))) = LED_GREEN;
    // // above you had to shift the LED_GREEN by two bits to take into the account size of the register which is 4 bytes wide
    // 
    // GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED;
    // // in the pointer arithmetic above you dont have to offset because it is done for you
    //
    // so far we've been using the APB (older, default one) bus
    // but we can alsu use the faster AHB
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
    
    while(1) {
        //GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED;
        GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
        int volatile counter = 0;
        while (counter < INTERVAL) {
                ++counter;
        }
        
        //GPIO_PORTF_DATA_BITS_R[LED_RED] = 0;
        GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = 0;
        counter = 0;
        while (counter < INTERVAL) {
                ++counter;
        }

    }
 
    return 0;
}


/*
void delay(int iter);

void delay(int iter) {
	int volatile counter;
	counter = 0;
	while (counter < iter) {
			++counter;
		}
}

int main()
{

	SYSCTL_RCGCGPIO_R |= (1U << 5); // enable clock for gpiof
	SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable AHB for GPIOF
	GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  	GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
  	
	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] |= LED_BLUE; //blue on
	
	while(1) {
	  	GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] |= LED_RED;
	 	delay(5000000/8);
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
		delay(2500000/16);
  	}
 
  return 0;
}
*/