// Board support package

// my addition cause something is not quite ok with
#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif
//

#include "tm4c_cmsis.h"
#include "bsp.h"

__stackless void assert_failed(char const *file, int line) { //does not acces stack impossible to return fron
	/* TODO: damage control */
	NVIC_SystemReset(); //reset the system
}

void SysTick_Handler(void) {
	//GPIOF_HS->DATA_Bits[LED_RED] ^= LED_RED; // toogling a bit
}