#include <stdint.h>

//#include "lm4f120h5qr.h"
#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;
//compiler


typedef /*__packed*/ struct { // this declares no storage
  uint8_t y;
  uint16_t x;
} Point;

typedef struct {
  Point top_left;
  Point bottom_right;
} Window;

typedef struct {
    Point corners[3];
} Triangle;

// struct Point pa, pb;

//typedef struct Point Point;

Point p1, p2;
Window w1, w2;
Triangle t;

int main()
{
    Point *pp;
    Window *wp;
    
    p1.x = sizeof(Point);
    p1.y = 0xaau;
  
    w1.top_left.x = 2u;
    w1.bottom_right.y = 3u;
    
    t.corners[0].x = 1u;
    t.corners[1].y = 2u;
    
    p2 = p1;
    w2 = w1;
    
    pp = &p1;
    wp = &w2;
    
    (*pp).x = 1u;
    
    pp->y = 5u;
    
    SYSCTL->RCGC2 |= (1U << 5); // enable clock for gpiof
    SYSCTL->GPIOHSCTL |= (1U << 5); // enable AHB for GPIOF
    GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIOF_HS->DATA_Bits[LED_BLUE] |= LED_BLUE; //blue on
    
    while(1) {
        GPIOF_HS->DATA_Bits[LED_RED] |= LED_RED;
        int volatile x = 5000000/8;
        delay(x);
        GPIOF_HS->DATA_Bits[LED_RED] = 0;
        delay(x/2);
    }
    
//    SYSCTL_RCGCGPIO_R |= (1U << 5); // enable clock for gpiof
//    SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable AHB for GPIOF
//    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
//    GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
//    
//    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] |= LED_BLUE; //blue on
//    
//    while(1) {
//            GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] |= LED_RED;
//            int volatile x = 5000000/8;
//            delay(x);
//            GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
//            delay(x/2);
//    }
 	
  return 0;
}




//#ifndef __FPU_PRESENT
//#define __FPU_PRESENT 1U
//#endif
//
//#include "tm4c_cmsis.h"
//#include "delay.h"
//
//#define LED_RED		(1u << 1)
//#define LED_BLUE	(1u << 2)
//#define LED_GREEN	(1u << 3)
//
//int main()
//{
//	SYSCTL->RCGC2 |= (1U << 5); // enable clock for gpiof
//	SYSCTL->GPIOHSCTL |= (1U << 5); // enable AHB for GPIOF
//	GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
//  	GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
//  	
//	GPIOF_HS->DATA_Bits[LED_BLUE] |= LED_BLUE; //blue on
//	
//	while(1) {
//	  	GPIOF_HS->DATA_Bits[LED_RED] |= LED_RED;
//	 	int volatile x = 5000000/8;
//		delay(x);
//		GPIOF_HS->DATA_Bits[LED_RED] = 0;
//		delay(x/2);
//  	}
// 
//  return 0;
//}