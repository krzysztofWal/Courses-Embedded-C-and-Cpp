#include "lm4f120h5qr.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

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
