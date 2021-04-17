#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"

bool push(uint32_t *arr, uint32_t index, uint32_t value, uint32_t *size, uint32_t *capacity) {
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

int main() {
  	
	  	//	================================= 
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
	// enable clock to UART
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
//	GPIOPinConfigure(GPIO_PA0_U0RX);
//   GPIOPinConfigure(GPIO_PA1_U0TX);
//    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
//	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
//                           (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
//                             UART_CONFIG_PAR_NONE));
	//	=================================
  
	//char value = 15;
	uint32_t size = 0;
	uint32_t capacity = 2;
	uint32_t* arr = (uint32_t*)(malloc(2 * sizeof(uint32_t))); //initial capacity = 2
	
	if (arr == NULL) {
		return 1;
	}
	
	printf("%x\r\n%u\r\n",arr, sizeof(uint32_t));
	
	push(arr, 0, 1, &size, &capacity);
   	push(arr, 1, 2, &size, &capacity);
   	push(arr, 2, 3, &size, &capacity);
    push(arr, 3, 4, &size, &capacity);
	
	printf("%u\r\n",arr[0]);
	printf("%u\r\n",arr[1]);
	printf("%u\r\n",arr[2]);
	printf("%u\r\n",arr[3]);
	
	free(arr);
	
  	return 0;
}
