#ifndef MIROS_H
#define MIROS_H

/* Thread COntrol Block (TCB)*/

typedef struct {
		void *sp; //stack pointer
} OSThread;

//pointer to thread function () that returns void and takes no arguments
typedef void (*OSThreadHandler)();

void OS_init(void);

/* this function must be called whith interrupts DISABLED */
void OS_sched(void);

void OSThread_start(
	OSThread *me, //a pointer to the TCB
	OSThreadHandler threadHandler, 
	void *stkSto, uint32_t stkSize);

#endif // MIROS_H
