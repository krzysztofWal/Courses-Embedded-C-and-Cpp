#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

//unsigned fact(unsigned n);

void swap(int *x, int *y);

void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

int main()
{
	int x = 1;
	int y = 2;
	swap(&x, &y);
//	x = fact(0u);
//	x = 2u + 3u * fact(1u);
//  	(void)fact(7u);
	  
	SYSCTL_RCGCGPIO_R |= (1U << 5); // enable clock for gpiof
	SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable AHB for GPIOF
	GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  	GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
  	
	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] |= LED_BLUE; //blue on
	
	while(1) {
	  	GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] |= LED_RED;
	 	int volatile x = 5000000/8;
		delay(x);
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
		delay(x/2);
  	}
 
  return 0;
}
/*
unsigned fact(unsigned n) {
	// 0! = 1
  	// n! = n*(n-1)! for n > 0
  	unsigned foo[6]; 
	foo[n] = n; <-- n = 7 -> corrupting lr value on a stack
  
  	if (n == 0u) {
		return 1u;
	} else {
		return foo[n] * fact(n - 1);
	}
}*/