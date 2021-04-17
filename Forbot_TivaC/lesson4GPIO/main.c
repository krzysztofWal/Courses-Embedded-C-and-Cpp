#define MEGA 1000000
#define KILO 1000
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "tm4c_cmsis.h"
#include "inc/hw_nvic.h"

#define LED_RED (1u << 1)

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
//#include "inc/hw_ints"
 

//int ktoreDiodeWPaske = 0;

int32_t n = 0;
int32_t nTegoFaceta = 7;
int32_t ifUp = 1;
uint32_t toWrite = 0;

uint32_t pinNums[8] = {GPIO_PIN_0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_6 , GPIO_PIN_7, GPIO_PIN_0, GPIO_PIN_1};
uint32_t pos[8] = {0, 1, 2 ,3, 6, 7, 0 ,1};
uint32_t base[8] = {GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTB_AHB_BASE, GPIO_PORTB_AHB_BASE};
uint32_t dir = 1;

uint32_t buttonState, reading, previousState = 1;

uint32_t buttonBegin = 0;
uint32_t debounceCounter = 0;

const uint32_t debounceTime  = 30;
const int blinkTime = 100;

volatile uint32_t timer_ms = 500;

void SysTickHandler() {
  	
  	if (timer_ms) {
  		timer_ms--;
  	}
	
  	if (buttonBegin) {
  		debounceCounter++;
	}
}

void sterujDiodami() {	
	if (dir == 1) {
		if (n == 0) {
			GPIOPinWrite(base[7], pinNums[7], 0x0);
		} else {
			GPIOPinWrite(base[n-1], pinNums[n-1], 0x0);	
		} 

		GPIOPinWrite(base[n], pinNums[n], (1 << pos[n]));
		
		if (n == 7) {n = 0;}
		else {n++; }
	} else {
		if (n == 7) {
			GPIOPinWrite(base[0], pinNums[0], 0x0);
		} else {
			GPIOPinWrite(base[n+1], pinNums[n+1], 0x0);	
		} 
		
		GPIOPinWrite(base[n], pinNums[n], (1 << pos[n]));
		
		if (n == 0) {n = 7;}
		else {n--;}
	}
}

// to ponizej niechcacy wyszlo przeliczenie na binarny na diodach
void writeToCorrespondingLed(int number) {
  for (uint8_t i = 0; i < 8; i++)
  if ((int)(number & (1u << i))) {
  //	GPIOPinWrite(base[i])	
		HWREG(base[i] + pinNums[i] * 4) = (1u << pos[i]);
  } else {
  		HWREG(base[i] + pinNums[i] * 4) = 0;
  }
}

void sterujDiodamiTegoFacetaCos() {
  	writeToCorrespondingLed(toWrite);	
  	toWrite += ifUp * (1u << nTegoFaceta);
	if (nTegoFaceta == 0) {
	  	nTegoFaceta = 7;
	  	ifUp = (ifUp == 1) ? -1 : 1;
	} else {
		nTegoFaceta--;
	}

}

int main()
{
  
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	// 40 000 000 Hz
	SysTickPeriodSet(40 * KILO );
    SysTickEnable();
    SysTickIntEnable();
    
	
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//	SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
// 	GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	//=================================================================//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
	
	
	//GPIOIntEnable(GPIO_PORTF_AHB_BASE, GPIO_PIN_4);
	//GPIOIntTypeSet(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, GPIO_LOW_LEVEL);
	
	//IntEnable(INT_GPIOF_TM4C123);
	//IntPrioritySet(INT_GPIOF_TM4C123, 0x00);
	
	//=================================================================//
	IntMasterEnable();
	
	GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOD);
 	GPIOPinTypeGPIOOutput(GPIO_PORTD_AHB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 | GPIO_PIN_7);

	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOB);
 	GPIOPinTypeGPIOOutput(GPIO_PORTB_AHB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	
	GPIOPinWrite(GPIO_PORTD_AHB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 | GPIO_PIN_7, 0x0);
	GPIOPinWrite(GPIO_PORTB_AHB_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0x0);
	
	// unlocking the GPIOCR Register
	HWREG(0x4005B520) = 0x4C4F434B;
	// enabling the pin
	GPIOUnlockPin(GPIO_PORTD_AHB_BASE, GPIO_PIN_7);
	// locking the register GPIOCR
	HWREG(0x4005B520) = 0x0;
	
	
	while(1) {
		
	  	if (timer_ms == 0) {
			sterujDiodamiTegoFacetaCos();
			timer_ms = blinkTime;
		}
	  
	  
	  
	  	/*	
	  	reading = GPIOPinRead(GPIO_PORTF_AHB_BASE, GPIO_PIN_4);
		
		if (reading != previousState ) {
			buttonBegin = 1;
		}
		
		if (debounceCounter > debounceTime) {
			buttonBegin = 0;
			debounceCounter = 0;
			if (buttonState != reading) {
				buttonState = reading;
			}
			if (buttonState == 0) {
				dir = (dir == 0) ? 1 : 0;
				// wyzeruj licznki (od razu po nacisnieciu)
				timer_ms = 0;
				// cofnij albo dodaj do n zeby nie zapalalo nastepnej diody po zmianie kierunku
		
				if (dir) {
				  	n = (n == 7) ? 0 : (n + 1);
				} else {
				  	n = (n == 0) ? 7 : (n - 1);
				}

				
			} 
		}
		previousState = reading;
		*/
	}
	

	  
	return 0;
}
