#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM
#endif

#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif

#include "inc/hw_types.h"
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "examples/boards/ek-tm4c123gxl/drivers/rgb.h"
#include "inc/hw_timer.h"
#include "tm4c_cmsis.h"
#include "driverlib/rom_map.h"

int main()
{
 	int ul_period = 1000; // with a 16-bit timer, maximum is 65535
	int duty_cycle = 250; // 75 % duty cycle (0.25 * ulPeriod)
  
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  	
	SYSCTL->RCGC1 |= (1u << 16);
	//ensuring timer is disabled
	TIMER0->CTL |= (0u << 8);
	//16-bit timer configuration
	TIMER0->CFG |= (1u << 2);
	//				PWM mode enabled	Edge_Time mode	Periodic_Timer mode
	TIMER0->TBMR = 0x0au;
	//inverting the signal
	TIMER0->CTL |= (1u << 14);
	//"beginning" value
	TIMER0->TBILR = 999;
	//"match" value
	TIMER0->TBMATCHR = 980;
	//enable timer
	TIMER0->CTL |= (1u << 8);
 	
	//enabling port F
	SYSCTL->RCGC2 |= (1u << 5);
	//portf are controlled by alternate hardware functions
	GPIOF->AFSEL |= (1u << 1);
	// writing into PMC1 of port f1
	GPIOF->PCTL = 0x00007770u;
	//enabling digital output at port 1
	GPIOF->DEN  |= (1u << 1);
	
	while(1) { // The following code varies the duty cycle over time
    	//TimerMatchSet(TIMER0_BASE, TIMER_B, duty_cycle++);
	  	TIMER0->CTL &= ~(1u << 8);
		TIMER0->TBMATCHR = duty_cycle++;
    	TIMER0->CTL |= (1u << 8);
		if(duty_cycle >= ul_period - 1)
            duty_cycle = 0;

        SysCtlDelay(50000);
    }

	return 0;
}