#include <stdint.h>
#include "bsp.h"

//stack for the first main
uint32_t stack_blinky1[40];
uint32_t *sp_blinky1 = &stack_blinky1[40];

/* background code: sequential with blocking version */
int main_blinky1() {
    while (1) {
				BSP_ledBlueOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledBlueOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}


//stack for the second main
uint32_t stack_blinky2[40];
uint32_t *sp_blinky2 = &stack_blinky2[40];


int main_blinky2() {
    while (1) {
				BSP_ledGreenOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}

int main() {

		BSP_init();
	
		/* fabricate Cortex-M ISR stack frame for blinky1 */
		
		// fabricated programme status register (PSR)
		*(--sp_blinky1) = (1U << 24); //xPSR
		// pc register - pointer ro a function (a cast so it fits into 32bit registers)
		*(--sp_blinky1) = (uint32_t)&main_blinky1;
		// rest for debugging reasons, as nothing is returned
		*(--sp_blinky1) = 0xeu; // lr
		*(--sp_blinky1) = 0xcu; // r12
		*(--sp_blinky1) = 0x3;	// r3
		*(--sp_blinky1) = 0x2;	// r2
		*(--sp_blinky1) = 0x1;	// r1
		*(--sp_blinky1) = 0x0;	// r0
		
		/* fabricate Cortex-M ISR stack frame for blinky2 */
		
		// fabricated programme status register (PSR)
		*(--sp_blinky2) = (1U << 24); //xPSR
		// pc register - pointer ro a function (a cast so it fits into 32bit registers)
		*(--sp_blinky2) = (uint32_t)&main_blinky2;
		// rest for debugging reasons, as nothing is returned
		*(--sp_blinky2) = 0xeu; // lr
		*(--sp_blinky2) = 0xcu; // r12
		*(--sp_blinky2) = 0x3;	// r3
		*(--sp_blinky2) = 0x2;	// r2
		*(--sp_blinky2) = 0x1;	// r1
		*(--sp_blinky2) = 0x0;	// r0
		
		while(1) {
		}
		
		// first free bit (sp shows last used stack entry)
    //return 0;
}
