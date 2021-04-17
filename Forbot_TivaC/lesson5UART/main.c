#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include <math.h>

uint32_t pinNums[8] = {GPIO_PIN_0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_6 , GPIO_PIN_7, GPIO_PIN_0, GPIO_PIN_1};
uint32_t pos[8] = {0, 1, 2 ,3, 6, 7, 0 ,1};
uint32_t base[8] = {GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTD_AHB_BASE, GPIO_PORTB_AHB_BASE, GPIO_PORTB_AHB_BASE};

void sendString(const uint8_t *pui8Buffer) {
    while(*pui8Buffer)
    {
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

char receiveChar(void) {
	char c;
	while (!UARTCharsAvail(UART0_BASE));
	c = HWREG(UART0_BASE + UART_O_DR);
	return c;
}

 //general options - that thing with semihosting (__write)
int putchar(int c) {
    UARTCharPut(UART0_BASE, (uint8_t)c);
    return c;
}

bool push(uint32_t *arr, volatile uint32_t index, uint32_t value, uint32_t *size, volatile uint32_t *capacity) {
  	if (*size > * capacity) {
  		arr = (uint32_t *)realloc(arr, sizeof(arr) * 2);
		*capacity = sizeof(arr) * 2;
	}
	if (arr != NULL) {
		arr[index] = value;
    	*size = *size + 1;
		return true;
	} else {
		return false;
	}
}

int32_t charToInt(uint32_t *arr, volatile uint32_t index) { // returns -1 if invalid input
  	int32_t result = 0;
  	int32_t tWP;
	int32_t number;
	// theoretically od tylu bylo by ciut wydajniej bo bez tego odejmowania za kazdym razem ale to tam szczegoly
	for (uint8_t i = 0; i < index ; i++) {
	  	if (arr[i] < 58 && arr[i] > 47) {
		  //	number = arr[i] - 48;
		  //	tWP = index - i - 1;
			result += (arr[i] - 48) * (int32_t)pow(10,index - i - 1);
		} else {
		  	result = -1;
			break;
		}
	}
	if (result > 255) {result = -1;}
	return result;
}

void writeToCorrespondingLed(int number) {
  for (uint8_t i = 0; i < 8; i++)
	  if ((int)(number & (1u << i))) {
	  //	GPIOPinWrite(base[i])	
			HWREG(base[i] + pinNums[i] * 4) = (1u << pos[i]);
	  } else {
			HWREG(base[i] + pinNums[i] * 4) = 0;
	  }
}

int main()
{

	
  	//	=================================  UART
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
	// enable clock to UART
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
	//	=================================
	
	// ================================== LEDs (including the speszjal one)
	
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
	
	// =================================
	
	
	/* // ====== swiecenie kolorkowymi diodami
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
 	GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x0);
	char value
	*/
	char value;
	uint32_t size = 0;
	volatile uint32_t capacity = 2;  //initial capacity = 2
	volatile uint32_t index = 0;
	bool reallocationStatus = true;
	uint32_t intValue;
	
	uint32_t* arr = (uint32_t*)(malloc(capacity * sizeof(uint32_t)));
	if (arr != NULL) {
	  	sendString("\r\nEnter a number between 1 and 255: ");
		do {
			//printf("Hello world!\r\n");
			//printf("%d",sizeof(int));
			/*sendString("Enter \"r\", \"g\" or \"b\":\r\n");
			value = receiveChar();
			sendString("\n\r");
			switch (value) {
			case 'r':
				GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
				break;
			case 'b':
				GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_2);
				break;
			case 'g':
				GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
				break;
			default:
				GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x0);
			}*/
			do {
				value = receiveChar();
				UARTCharPut(UART0_BASE, value);
				reallocationStatus = push(arr, index++, value, &size, &capacity);
			} while (value != '\r' && reallocationStatus != false);
			UARTCharPut(UART0_BASE,'\n');
			//check if the input is valid and convert it to an int
			intValue = charToInt(arr, --index);
			
			if (intValue != -1) {
			  	writeToCorrespondingLed(intValue);
				sendString("\Enter a number between 1 and 255: ");
			} else {
			  sendString("Incorrect input, try again: ");
			}
			
			index = 0;			
			
		} while (1 & reallocationStatus == true);
		
		if (!reallocationStatus) {
			sendString("Memory reallocation failed");
		}
		
	} else {
		sendString("Memory allocation failed\r\n");
	}
	
  	return 0;
}
