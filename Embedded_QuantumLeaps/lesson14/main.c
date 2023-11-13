// my addition cause something is not quite ok with
#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif


#include <stdint.h>

//#include "lm4f120h5qr.h"
#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)


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


Point p2;
Window w2;
Triangle t;

Point p1 = { 1u, 2u};
Window w1 = { {123u, 1234u}, {234u, 6789u}}; // with {1,2} {3,4}unsigned here, still packbit



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
//uint16_t x = -1;
//uint32_t y = LED_RED | LED_GREEN;
//
//int16_t sqr[3] = {
//	1*1,
//	2*2
//};
//
//typedef struct {
//	uint8_t y;
//	uint16_t x;
//} Point;
//
//Point p1 = {
//	123u,
//	0X1234u
//};
//Point p2;
//
//typedef struct {
//	Point top_left;
//	Point bottom_right;
//} Window;
//
//typedef struct {
//	Point corners[3];
//} Triangle;
//
//Window w = {
//  {123U, 0x1234U},
//  {234U, 0x6789U}
//};
//
//Window w2;
//Triangle t;
//
//int main()
//{
//  	Point *pp;
//    Window *wp;
//  
//    p1.x = sizeof(Point);
//    p1.y = 0xAAU;
//    
//    w.top_left.x = 1U;
//    w.bottom_right.y = 2U;
//    
//    t.corners[0].x = 1U;
//    t.corners[2].y = 2U;
//    
//    p2 = p1;
//    w2 = w;
//    
//    pp = &p1;
//    wp = &w2;
//    
//    (*pp).x = 1U;
//    
//    (*wp).top_left = *pp;
//    
//    pp->x = 1U;
//    wp->top_left = *pp;
//	
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