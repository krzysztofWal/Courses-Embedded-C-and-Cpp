#ifndef __FPU_PRESENT
#define __FPU_PRESENT 1U
#endif

#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

uint16_t x = -1;
uint32_t y = LED_RED | LED_GREEN;

int16_t sqr[3] = {
	1*1,
	2*2
};

typedef struct {
	uint8_t y;
	uint16_t x;
} Point;

Point p1 = {
	123u,
	0X1234u
};
Point p2;

typedef struct {
	Point top_left;
	Point bottom_right;
} Window;

typedef struct {
	Point corners[3];
} Triangle;

Window w = {
  {123U, 0x1234U},
  {234U, 0x6789U}
};

Window w2;
Triangle t;

int main()
{
  	Point *pp;
    Window *wp;
  
    p1.x = sizeof(Point);
    p1.y = 0xAAU;
    
    w.top_left.x = 1U;
    w.bottom_right.y = 2U;
    
    t.corners[0].x = 1U;
    t.corners[2].y = 2U;
    
    p2 = p1;
    w2 = w;
    
    pp = &p1;
    wp = &w2;
    
    (*pp).x = 1U;
    
    (*wp).top_left = *pp;
    
    pp->x = 1U;
    wp->top_left = *pp;
	
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