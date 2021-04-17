#define UART0_BASE              0x4000C000 
#define GPIO_PORTA_BASE         0x40004000
#include "examples/boards/ek-tm4c123gxl/forbot/myUart.h" 
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"
#include  "inc/tm4c123gh6pm.h"

#include "driverlib/timer.h"
//#include "/examples/boards/ek-tm4c123gxl/forbot/myUart.h" 



#ifdef DEBUG 
void__error__(char *pcFilename, unsigned long ulLine) 
{ 
} 
#endif 

#define SYSTICK_TIME_MS 100

bool intSysTickFlag = false;
volatile uint32_t timer_ms = SYSTICK_TIME_MS;
uint32_t debugCount = 0;

bool getData = false;

void ADCIntHandler () {
	//clear the interrupt flag
  	ADCIntClear(ADC0_BASE, 0);
  //ADCIntClear(ADC0_BASE, 1); 
	getData = true;
	//sendUnsignedInt(debugCount++);
	//sendString("\r\n");
}
int main()
{
  

	uint32_t ulADC0Value[4];

	volatile unsigned long ulTempAvg; 
	volatile unsigned long ulTempValueC; 
	volatile unsigned long ulTempValueF; 
	
//	PLL must be enabledd and programmed to the desired frquency, default is 16Mhz which is supported ; 
//	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); 
	/*
//  SysTickIntEnable();
//	IntMasterEnable();
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT |  SYSCTL_XTAL_16MHZ);
	// ============================ TIMER ======================================== //
	// https://e2e.ti.com/support/microcontrollers/other/f/908/t/498565?REG-Timer-interrupt-generation-in-TM4C123GH6PM-Launchpad
	// ^ using tivaWare
	// enabling clock to timer
	SYSCTL_RCGCTIMER_R |= 1;
	TIMER0_CTL_R &= ~1; //disable timer
	TIMER0_CFG_R |= 0x00000000; 
	TIMER0_TAMR_R |= (1u << 1); //periodic
	//TIMER0_TAILR_R = 4294967296 - 1;
	TIMER0_TAILR_R = 16000000 * 1.5 - 1;
	// 20 probek na sek czyli co 50 ms, przy taktowaniu 64 000 Hz daje to 64000 * 50 / 1000 = 640*5
	//TIMER0_TAPR_R = 2 - 1; // prescaler 
	//IntEnable(INT_TIMER0A);
	//TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); 	//TIMER0_IMR_R |= 1;
	//enable triggering in timer
	TIMER0_CTL_R |= (1u << 5);
	TIMER0_CTL_R |= 0x01; //enable timer
	

	// ============================ ADC ========================================== //
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);	
	//disabling in oredr to configure the sequencer settings
	ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_HALF, 1);
	ADCSequenceDisable(ADC0_BASE, 1); 
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_TIMER, 0); 
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH2); 
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH2); 
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2); 
	ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END); 
	ADCSequenceEnable(ADC0_BASE, 1); 
	TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
	ADC0_IM_R |= 2u; // raw interrupt mask;
	IntEnable(INT_ADC0SS1);
//	ADCIntEnable(ADC0_BASE, 1);
	
	*/
	// =======================================================================//
	    //
    // Use ADC0 sequence 0 to sample channel 3 once for each timer period.
    //
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_HALF, 1);

    //
    // Wait for the clock configuration to set.
    //
    SysCtlDelay(10);

    //
    // Disable the ADC0 sequence 0 interrupt on the processor (NVIC).
    //
    IntDisable(INT_ADC0SS0);

    //
    // Disable interrupts for ADC0 sample sequence 0 to configure it.
    //
    ADCIntDisable(ADC0_BASE, 0);

    //
    // Disable ADC0 sample sequence 0.  With the sequence disabled, it is now
    // safe to load the new configuration parameters.
    //
    ADCSequenceDisable(ADC0_BASE, 0);

    //
    // Enable sample sequence 0 with a processor signal trigger.  Sequence 0
    // will do a single sample when the processor sends a signal to start the
    // conversion.
    //
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0);

    //
    // Configure step 0 on sequence 0.  Sample channel 3 (ADC_CTL_CH3) in
    // single-ended mode (default) and configure the interrupt flag
    // (ADC_CTL_IE) to be set when the sample is done.  Tell the ADC logic
    // that this is the last conversion on sequence 0 (ADC_CTL_END).  Sequence
    // 0 has 8 programmable steps.  Since we are only doing a single conversion
    // using sequence 0 we will only configure step 0.  For more information
    // on the ADC sequences and steps, reference the datasheet.
    //
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH2 | ADC_CTL_END |
                             ADC_CTL_IE);

    //
    // Since sample sequence 0 is now configured, it must be enabled.
    //
    ADCSequenceEnable(ADC0_BASE, 0);

    //
    // Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample.
    //
    ADCIntClear(ADC0_BASE, 0);

    //
    // Enables the DMA channel for the ADC0 sample sequence 0.
    //
    ADCSequenceDMAEnable(ADC0_BASE, 0);

    //
    // Enable the ADC 0 sample sequence 0 interrupt.
    //
    ADCIntEnable(ADC0_BASE, 0);

    //
    // Enable the interrupt for ADC0 sequence 0 on the processor (NVIC).
    //
    IntEnable(INT_ADC0SS0);
	//==============================================================================
	    //
    // Configure a 16-bit periodic timer.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);

    //
    // Set ADC sampling frequency to be 16KHz i.e. every 62.5uS.
    //
    TimerLoadSet(TIMER0_BASE, TIMER_A, 64000 - 1);

    //
    // Enable the ADC trigger output for Timer A.
    //
    TimerControlTrigger(TIMER0_BASE, TIMER_A, true);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    //
    // Enable Timer 0 which will start the whole application process.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);
	// ============================================================================

	// setting pin PE1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIO_PORTE_AFSEL_R |= (1u << 1);
	GPIO_PORTE_DEN_R &= ~(1u << 1);
	GPIO_PORTE_AMSEL_R |= (1u << 1);
	
	UART0Init_115200_8_N_1();
	
	//IntMasterEnable();
	
	while(1) 
	{
	  	/* The indication that the ADC conversion is complete will be the ADC interrupt status flag. 
		It’s always good programming practice to make sure that the flag is cleared before 
		writing code that depends on it. Add the following line as your first line of code inside 
		the while(1) loop: */
	  /*	
	  ADCIntClear(ADC0_BASE, 1); 
	  	// triggering with the software
	  	ADCProcessorTrigger(ADC0_BASE, 1); 
		
		while(!ADCIntStatus(ADC0_BASE, 1, false)) 
			{ getData = true; 
			}
	*/	
//	  	if (getData) {
		if(getData == true) {
			ADCSequenceDataGet(ADC0_BASE, 0, ulADC0Value);
	//		 The addition of 2 is for rounding. Since 2/4 = 1/2 = 0.5, 1.5 will be rounded to 2.0 with 
		//	te addition of 0.5. In the case of 1.0, when 0.5 is added to yield 1.5, this will be rounded 
		//	back down to 1.0 due to the rules of integer math. */  
			ulTempAvg = (ulADC0Value[0] + ulADC0Value[1] + ulADC0Value[2] + ulADC0Value[3] + 2)/4; 
			sendUnsignedInt(*ulADC0Value);
			sendString(" ");
			sendUnsignedInt(debugCount);
			sendString("\r\n");
			getData = false;
			debugCount = 0;
			getData = false;
		}
			
	}

	
	
	return 0;
	
}
