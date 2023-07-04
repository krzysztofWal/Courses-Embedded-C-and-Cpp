
#include "lm4f120h5qr.h"
#include "delay.h"
#include <stdint.h>

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

#define INTERVAL 1250000

unsigned fact(unsigned n);

int main()
{
    unsigned volatile x = 5;
    
    x = fact(0u);
    (void)fact(5u); // to signal that you do not
    
    
    while(1) {;}
    /*
    SYSCTL_RCGCGPIO_R |= (1U << 5); // clock gating for gpio port f
  
    SYSCTL_GPIOHBCTL_R |= (1u << 5); // enable the AHB for gpio port f
    
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
    
    while(1) {
        delay(INTERVAL);
        GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
        delay(INTERVAL);
        GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = 0;
    }
    */
    return 0;
}

unsigned fact(unsigned n)
{
  // recursive aproach
  if (n == 0u)
  {
    return 1u;
  }
  else
  {
    return n * fact(n - 1u);
  }
}

/*

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;
//compiler


int8_t s8;
int16_t s16;
int32_t s32;

int main()
{
  	u8a = sizeof(u8a);
	u16c = sizeof(uint16_t);
	u32e = sizeof(uint32_t);
	
	u8b  = u8a;
    u16d = u16c;
    u32f = u32e;
    
    u16c = 40000U;
    u16d = 30000U;
	u32e = u16c + u16d;
	//before computation right side arguments are promoted to
	//int or uint so if it is 16-bit it would overflow
	// ============!==========
	// the precision in which the computanion is performed does not depend on lhs!!!!
	// ===============!==========
	// (it takes extra instructions)
	u32e = (uint32_t)u16c + u16d;

	u16c = 100U;
    s32  = 10 - u16c;  // NOT portable! both operands to unsigned in
    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 10 10
	// 00 00 00 00 00 00 00 00 00 00 00 00 01 10 01 00
	// 11 11 11 11 11 11 11 11 11 11 11 11 10 10 01 10  (2)= -90 mod maks_przy_32bit (10)
	// https://stackoverflow.com/questions/7221409/is-unsigned-integer-subtraction-defined-behavior
	// interpreted as signed gives - 90
	
	// using 16-bit we get 11 11 11 11 10 10 01 10
	// when cast to signed we get
	// 00 00 00 00 00 00 00 00 11 11 11 11 10 10 01 10
	
	//if (u32e > -1) {  // ALWAYS false! -1 converted to unsigned
    if ((int32_t)u32e > -1) {
        u8a = 1U;
    }
    else {
        u8a = 0U;
    }
	
	u8a = 0xffU;
    //if (~u8a == 0x00U) { // ALWAYS false! promotion to int and negating a lot of zeroes bwfore u8a (00)
    if ((uint8_t)(~u8a) == 0x00U) {
        u8b = 1U;
    }
	
	s32  = 10 - (int16_t)u16c;
	// now it uses signed intigers on the right
	
	
//	SYSCTL_RCGCGPIO_R |= (1U << 5); // enable clock for gpiof
//	SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable AHB for GPIOF
//	GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
//  	GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
//  	
//	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] |= LED_BLUE; //blue on
//	
//	while(1) {
//	  	GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] |= LED_RED;
//	 	int volatile x = 5000000/8;
//		delay(x);
//		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
//		delay(x/2);
//  	}
 	
  return 0;
}
*/