#include "lm4f120h5qr.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

int main()
{
  	unsigned int a = 0x5a5a5a5au;
	unsigned int b = 0xdeadbeefu;
	unsigned int c;
	
	c = a | b;
	c = a & b;
	c = a ^ b;
	c = ~b;
	c = b >> 1;
	c = b << 3;
	
	SYSCTL_RCGCGPIO_R |= (1U << 5);
	GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  	GPIO_PORTF_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
  	
	((volatile unsigned long *)(0x4005d000))[LED_BLUE] = LED_BLUE; //blue on
	
	while(1) {
	  	GPIO_PORTF_DATA_R |= LED_RED;
	 	unsigned int counter = 0;
		while (counter < 5000000) {
			++counter;
		}
		
		GPIO_PORTF_DATA_R   &= ~LED_RED;
		while (counter > 0) {
			--counter;
		}

  	}
 
  return 0;
}
