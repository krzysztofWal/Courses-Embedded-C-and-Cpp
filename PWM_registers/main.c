#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM
#endif

#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif

#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
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

//#define GPIO_PF1_T0CCP1		0x00050407

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
	
	//TimerLoadSet(TIMER0_BASE, TIMER_B, ul_period - 1);
	//TimerMatchSet(TIMER0_BASE, TIMER_B, duty_cycle);
	//TimerEnable(TIMER0_BASE, TIMER_B);
 	
	//enabling port F
	SYSCTL->RCGC2 |= (1u << 5);
	//portf are controlled by alternate hardware functions
	GPIOF->AFSEL |= (1u << 1);
	// writing into PMC1 of port f1
	GPIOF->PCTL = 0x00007770u;
	//enabling digital output at port 1
	GPIOF->DEN  |= (1u << 1);
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//	GPIOPinConfigure(GPIO_PF1_T0CCP1);
//	GPIOPinTypeTimer(GPIO_PORTF_BASE, 2u);
	
	while(1) { // The following code varies the duty cycle over time
    	//TimerMatchSet(TIMER0_BASE, TIMER_B, duty_cycle++);
	  	TIMER0->CTL &= ~(1u << 8);
		TIMER0->TBMATCHR = duty_cycle++;
    	TIMER0->CTL |= (1u << 8);
		if(duty_cycle >= ul_period - 1)
            duty_cycle = 0;

        SysCtlDelay(50000);
    }
	
	/*
	//
    // Enable the GPIO Port and Timer for each LED
    //
    MAP_SysCtlPeripheralEnable(RED_GPIO_PERIPH);
    MAP_SysCtlPeripheralEnable(RED_TIMER_PERIPH);

    MAP_SysCtlPeripheralEnable(GREEN_GPIO_PERIPH);
    MAP_SysCtlPeripheralEnable(GREEN_TIMER_PERIPH);

    MAP_SysCtlPeripheralEnable(BLUE_GPIO_PERIPH);
    MAP_SysCtlPeripheralEnable(BLUE_TIMER_PERIPH);

    //
    // Configure each timer for output mode
    //
    HWREG(GREEN_TIMER_BASE + TIMER_O_CFG)   = 0x04;
    HWREG(GREEN_TIMER_BASE + TIMER_O_TAMR)  = 0x0A;
    HWREG(GREEN_TIMER_BASE + TIMER_O_TAILR) = 0xFFFF;

    HWREG(BLUE_TIMER_BASE + TIMER_O_CFG)   = 0x04;
    HWREG(BLUE_TIMER_BASE + TIMER_O_TBMR)  = 0x0A;
    HWREG(BLUE_TIMER_BASE + TIMER_O_TBILR) = 0xFFFF;

    HWREG(RED_TIMER_BASE + TIMER_O_CFG)   = 0x04;
    HWREG(RED_TIMER_BASE + TIMER_O_TBMR)  = 0x0A;
    HWREG(RED_TIMER_BASE + TIMER_O_TBILR) = 0xFFFF;

    //
    // Invert the output signals.
    //
    HWREG(RED_TIMER_BASE + TIMER_O_CTL)   |= 0x4000;
    HWREG(GREEN_TIMER_BASE + TIMER_O_CTL)   |= 0x40;
    HWREG(BLUE_TIMER_BASE + TIMER_O_CTL)   |= 0x4000;
	
	MAP_TimerMatchSet(RED_TIMER_BASE, RED_TIMER, 0);
	MAP_TimerMatchSet(GREEN_TIMER_BASE, GREEN_TIMER, 0);
	MAP_TimerMatchSet(BLUE_TIMER_BASE, BLUE_TIMER, 240);
	
	//
    // Enable timers to begin counting
    //
    MAP_TimerEnable(RED_TIMER_BASE, TIMER_BOTH);
    MAP_TimerEnable(GREEN_TIMER_BASE, TIMER_BOTH);
    MAP_TimerEnable(BLUE_TIMER_BASE, TIMER_BOTH);
	
    //
    // Reconfigure each LED's GPIO pad for timer control
    //
    MAP_GPIOPinConfigure(GREEN_GPIO_PIN_CFG);
    MAP_GPIOPinTypeTimer(GREEN_GPIO_BASE, GREEN_GPIO_PIN);
    MAP_GPIOPadConfigSet(GREEN_GPIO_BASE, GREEN_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

    MAP_GPIOPinConfigure(BLUE_GPIO_PIN_CFG);
    MAP_GPIOPinTypeTimer(BLUE_GPIO_BASE, BLUE_GPIO_PIN);
    MAP_GPIOPadConfigSet(BLUE_GPIO_BASE, BLUE_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

    MAP_GPIOPinConfigure(RED_GPIO_PIN_CFG);
    MAP_GPIOPinTypeTimer(RED_GPIO_BASE, RED_GPIO_PIN);
    MAP_GPIOPadConfigSet(RED_GPIO_BASE, RED_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);
	
	while(1) {
		
	}
	*/
	return 0;
}