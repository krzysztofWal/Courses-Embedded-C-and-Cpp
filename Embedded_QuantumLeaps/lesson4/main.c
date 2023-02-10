#define RCGCGPIO (*((unsigned int *)0x400fe608u))
#define GPIOF_BASE 0x40025000u
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400u)))
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51cu)))
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3fcu)))

int main()
{
  
	//turning on the led
//  	*((unsigned int *)0x400fe608u) = 0x20u; //turning off clock-gating to gpio port f
		RCGCGPIO = 0x20u;
  //  	*((unsigned int *)0x40025400u) = 0x0eu; //gpio port f - out-direction (1,2,3)
		GPIOF_DIR = 0x0eu;
//  	*((unsigned int *)0x4002551cu) = 0x0eu; // digital (1,2,3)
  		GPIOF_DEN = 0x0eu;
  
  
	while(1) {
//  		*((unsigned int *)0x400253fcu) = 0x02u; // (1f - red colour)
	  	GPIOF_DATA = 0x02u;
	 	unsigned int counter = 0;
		while (counter < 5000000) {
			++counter;
		}
		
//		*((unsigned int *)0x400253fcu) = 0x04u; // (1f - red colour)
		GPIOF_DATA = 0x04u;
		while (counter > 0) {
			--counter;
		}
		
//		*((unsigned int *)0x400253fcu) = 0x08u; // (1f - red colour)
		GPIOF_DATA = 0x08u;
		while (counter < 5000000) {
			++counter;
		}
  	}
 
  return 0;
}
