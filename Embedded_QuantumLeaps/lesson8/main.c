#include "lm4f120h5qr.h"

#define LED_RED		(1u << 1)
#define LED_BLUE	(1u << 2)
#define LED_GREEN	(1u << 3)

#define INTERVAL 1250000

void delay(int iter);

void delay(int iter)
{
  int volatile counter = 0;
  while (counter < iter)
  {
          ++counter;
}

}
int main()
{
  
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
 
    return 0;
}
