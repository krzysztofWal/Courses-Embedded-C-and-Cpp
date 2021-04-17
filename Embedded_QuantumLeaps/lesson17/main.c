#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif

#include "tm4c_cmsis.h"
#include "bsp.h"
#include "intrinsics.h"

int main()
{
	SYSCTL->RCGC2 |= (1U << 5); // enable clock for gpiof
	SYSCTL->GPIOHSCTL |= (1U << 5); // enable AHB for GPIOF
	GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
  	GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
  
	SysTick->LOAD = SYS_CLOCK_HZ/2u - 1u;
	SysTick->VAL = 0u;
	SysTick->CTRL = (1u << 2) | (1u << 1) | 1u;
	
	__enable_interrupt();
	
	while(1) {
  		GPIOF_HS->DATA_Bits[LED_GREEN] ^= LED_GREEN;
		GPIOF_HS->DATA_Bits[LED_GREEN] ^= LED_GREEN;
	}
 
  return 0;
}