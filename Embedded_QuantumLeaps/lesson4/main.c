// lesson four

/*
#define CLOCK_GATING_ONE (*((unsigned int *)0x400fe608u))
#define GPIOF_DIR_ONE (*((unsigned int *)0x40025400u))
#define GPIOF_DEN_ONE (*((unsigned int *)0x4002551cu))
#define GPIOF_DATA_ONE (*((unsigned int *)0x400253fcu))

#define FIRST_INTERVAL 3000000

int main()
{
  // this is a bit hard-coded in 
  // when it comes to setting bits
  CLOCK_GATING_ONE = 0x20u; // clock-gating
  GPIOF_DIR_ONE = 0x0eu; // gpiodir
  GPIOF_DEN_ONE = 0x0eu; // gpioden
  
  int i;
  while (1)
  {
    // set the first bit
    GPIOF_DATA_ONE |= 1u << 1;
    for ( i = 0; i < FIRST_INTERVAL; i++ ) { ; }
    // unset the first bit
    GPIOF_DATA_ONE &= ~(1u << 1);
    for ( i = 0; i < FIRST_INTERVAL; i++ ) { ; }
  }
}
*/

// lesson five

// #define RCGCGPIO (*((unsigned int *)0x400fe608u))
// #define GPIOF_BASE 0x40025000u
// #define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400u)))
// #define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51cu)))
// #define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3fcu)))

#include "lm4f120h5qr.h"
#define INTERVAL 1250000

int main()
{
  
    SYSCTL_RCGCGPIO_R = 0x20u; //clock gating
    GPIO_PORTF_DIR_R = 0x0eu; // set as outputs (pins 1,2,3)
    GPIO_PORTF_DEN_R = 0x0eu; // digital outputs

    
    while(1) {
        GPIO_PORTF_DATA_R = 0x02u;
        volatile unsigned int counter = 0;
        while (counter < INTERVAL) 
        {
                ++counter;
        }
        GPIO_PORTF_DATA_R = 0x00u;
        counter = 0;
        while (counter < INTERVAL) 
        {
                ++counter;
        }
    }
 
    return 0;
}


