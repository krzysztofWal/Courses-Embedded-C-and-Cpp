// my addition cause something is not quite ok with
#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif
//

#include "tm4c_cmsis.h"

extern int CSTACK$$Limit; //declaration not definition, linker 
void __iar_program_start(void);
void Unused_Handler(void);

const int __vector_table[] @ ".intvec" = {
	(int)&CSTACK$$Limit,
	(int)&__iar_program_start, // reset - pc adress after a reset
        // these are common for all ARM COrtex-M
        // and are for handling standard  exceptions:
	(int)&NMI_Handler,
	(int)&HardFault_Handler,
	(int)&MemManage_Handler,
	(int)&BusFault_Handler,
	(int)&UsageFault_Handler,
	0, //reserved slots - usually 
	0,
	0,
	0,
	(int)&SVC_Handler,
	(int)&DebugMon_Handler,
	0,
	(int)&PendSV_Handler,
	(int)&SysTick_Handler
};
//you need to place the vector table in the right spot but it is red-only memory

__stackless void HardFault_Handler(void) {
	assert_failed("HardFault", __LINE__);
	//perform damage control, reset the machine, write to error log if possible
}

__stackless void NMI_Handler(void) {
	assert_failed("NMI", __LINE__);
}

__stackless void MemManage_Handler(void) {
	assert_failed("MemMenage", __LINE__);
}
 
__stackless void BusFault_Handler(void) {
	assert_failed("BusFault", __LINE__);
}

__stackless void UsageFault_Handler(void) {
	assert_failed("UsageFault", __LINE__);
}

__stackless void Unused_Handler(void) {
	assert_failed("Unused", __LINE__);
}

#pragma weak SVC_Handler		= Unused_Handler
#pragma weak DebugMon_Handler	= Unused_Handler
#pragma weak PendSV_Handler		= Unused_Handler
#pragma weak SysTick_Handler	= Unused_Handler