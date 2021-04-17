#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif

#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

int main()
{
	SYSCTL->RCGC2 |= (1U << 5); // enable clock for gpiof
	SYSCTL->GPIOHSCTL |= (1U << 5); // enable AHB for GPIOF
	GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
  	GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
  	
	GPIOF_HS->DATA_Bits[LED_BLUE] |= LED_BLUE; //blue on
	
	while(1) {
	  	GPIOF_HS->DATA_Bits[LED_RED] |= LED_RED;
	 	int volatile x = 5000000/8;
		delay(x);
		GPIOF_HS->DATA_Bits[LED_RED] = 0;
		delay(x/2);
  	}
 
  return 0;
}