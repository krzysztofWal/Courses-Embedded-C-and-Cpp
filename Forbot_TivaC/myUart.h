
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
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
#include  "inc/TM4C123GH6PM.h"

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

void sendUnsignedInt(uint32_t value) {
	char buff[10];
	uint8_t index = 0;
	if (value == 0) {
		UARTCharPut(UART0_BASE, 48);
	} else {
		while (value != 0) {
			//printf("%c",(char)(value % 10 + 48));
			buff[index++] = (value % 10 + 48);
			value = value / 10;
		}
		for (int8_t i = -- index ; i >= 0; i--) {
			//printf("%c" ,buff[i]);
			UARTCharPut(UART0_BASE, buff[i]);
		}
	}
}

void UART0Init_115200_8_N_1() {

	// enable clock to UART
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

}
