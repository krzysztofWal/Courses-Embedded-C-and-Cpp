#ifndef MIROS_H
#define MIROS_H

/* Thread COntrol Block (TCB)*/

typedef struct {
		void *sp; //stack pointer
		uint32_t timeout; /* timeout delay conter */
		uint8_t prio; /*thread priority*/
		
} OSThread;

//pointer to thread function () that returns void and takes no arguments
typedef void (*OSThreadHandler)();

void OS_init(void *stkSto, uint32_t stkSize);

/* callback to handle idle consitions*/
void OS_onIdle(void);

/* this function must be called whith interrupts DISABLED */
void OS_sched(void);

/* transfer control to RTOS to run the threads*/
void OS_run(void);

/* blocking delay */
void OS_delay(uint32_t ticks);

/* process all timeouts */
void OS_tick(void);

/* callback to configure and start interrupts*/
void OS_onStartup(void);

void OSThread_start(
	OSThread *me, //a pointer to the TCB
	uint8_t pri, // priority number
	OSThreadHandler threadHandler, 
	void *stkSto, uint32_t stkSize);



#endif // MIROS_H
