#include <stdint.h>
#include "miros.h"
#include "bsp.h"

uint32_t stack_blinky1[40];
OSThread blinky1;

void main_blinky1() {
    while (1) {
		uint32_t volatile  i;
		for (i = 1500U; i != 0; --i){
			BSP_ledRedOn();
			BSP_ledRedOff();
		}
		OS_delay(1u); /* delays for one clock tick */
    }
}

uint32_t stack_blinky2[40];
OSThread blinky2;

void main_blinky2() {
	while (1) {
		uint32_t volatile  i;
		for (i = 1500U; i != 0; --i){
			BSP_ledGreenOn();
			BSP_ledGreenOff();
		}
		OS_delay(50u); /* delays for one clock tick */
	}
}


uint32_t stack_blinky3[40];
OSThread blinky3;

void main_blinky3() {
	OS_delay(BSP_TICKS_PER_SEC / 2);
    while (1) {
		BSP_ledBlueOn();
        OS_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledBlueOff();
        OS_delay(BSP_TICKS_PER_SEC * 3 / 4U);
    }
}

uint32_t stack_idleThread[40];

int main() {

	BSP_init();
	OS_init(stack_idleThread, sizeof(stack_idleThread));

	OSThread_start(&blinky1,
				5u,
				&main_blinky1,
				stack_blinky1, sizeof(stack_blinky1));
	
	OSThread_start(&blinky2,
					2u,
					&main_blinky2,
					stack_blinky2, sizeof(stack_blinky2));

//	OSThread_start(&blinky3,
//					&main_blinky3,
//					stack_blinky3, sizeof(stack_blinky3));	
//		
	/* transfer control to the rtos to run the threads*/
	OS_run();

    //return 0;
}
