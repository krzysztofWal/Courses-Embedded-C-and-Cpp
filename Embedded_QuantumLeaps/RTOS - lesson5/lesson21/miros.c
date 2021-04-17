#include <stdint.h>
#include "miros.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

OSThread * volatile OS_curr; // pointer to current thread //used inside interrupts
OSThread * volatile OS_next; // pointer to the next thread to run

OSThread *OS_thread[32 + 1]; /* array of threads started*/
							/* now, index of the thread pointer corresponds to priority level of that tread*/
							/* [0] -> priority 0,[1] - > priority 1 and so on*/
uint32_t OS_readySet; /* bitmask of threads that are ready to run */
uint32_t OS_delayedSet; /* bitmask of threads thar are delayed */

#define LOG2(x) (32 - __clz(x)) /* integer aproximation of log2(x) - getting the priority of a ready thread with biggest priority*/
/*CLZ - counting leading zeroes*/

OSThread idleThread;
void main_idleThread() {
    while (1) {
		OS_onIdle();
    }
}


void OS_init(void *stkSto, uint32_t stkSize) {
	// setting the Pend SV interrupt priority to the lowest level
	*(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);

	/* start the idle thread */
	OSThread_start(&idleThread,0u,
					&main_idleThread,
					stkSto, stkSize);
	
}

void OS_sched(void) {
		
	/* OS_next = ... */
	
	if (OS_readySet == 0U)  {/* idle condition */
		OS_next = OS_thread[0]; /* priority 0 - idle thread*/
	} else {
		OS_next = OS_thread[LOG2(OS_readySet)];
		Q_ASSERT(OS_next != (OSThread *)0 );
	}
	/* trigger PendSV if needed+*/
	if (OS_next != OS_curr) {
		*(uint32_t volatile *)0xE000ED04 = (1u << 28); //svPend
	}
}

void OS_run(void) {
	/* 	callback to configure and start interrupts */
	OS_onStartup();

	__disable_irq();
	OS_sched();
	__enable_irq();

	/* the following code should naver execute */
	Q_ERROR();
}

void OS_tick(void) {
	uint32_t workingSet ;
	while (workingSet != 0u) {
		OSThread *t = OS_thread[LOG2(workingSet)];
		uint32_t bit = (1u << (t->prio - 1u));
		
		Q_ASSERT((t != (OSThread*)0) && (t->timeout != 0u));
		
		--t->timeout;
		if (t->timeout == 0u) {
			OS_readySet |= bit; // thread ready bit assert in bitmask
			OS_delayedSet &= ~bit;  // thread delay bit clear in bitmask
		}
		workingSet &= ~bit;
	}
}

void OS_delay(uint32_t ticks) {
	uint32_t bit;
	__disable_irq();
	
	/* never call OS_delay from the idleThread */
	Q_REQUIRE(OS_curr != OS_thread[0]);
	
	OS_curr->timeout = ticks;
	bit = (1u << (OS_curr->prio - 1u));
	OS_readySet &= ~bit; /* set corresponding bit in readySet bitmask to 0 - thread is not ready to run*/
	OS_delayedSet |= bit;
	OS_sched();
	__enable_irq();
}

void OSThread_start(
	OSThread *me, //a pointer to the TCB
	uint8_t prio,
	OSThreadHandler threadHandler, 
	void *stkSto, uint32_t stkSize)
{
	uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8) * 8); //rounding to the top of 8th byte boundary
	uint32_t *stk_limit;

	/* priority must be in range but also it must not have been used already */
	Q_REQUIRE((prio < Q_DIM(OS_thread))
			&& OS_thread[prio] == (OSThread*)0);
		
	
	/* fabricate Cortex-M ISR stack frame for blinky1 */
    *(--sp) = (1U << 24);  /* xPSR */
    *(--sp) = (uint32_t)(threadHandler); /* PC */
    *(--sp) = 0x0000000EU; /* LR  */
    *(--sp) = 0x0000000CU; /* R12 */
    *(--sp) = 0x00000003U; /* R3  */
    *(--sp) = 0x00000002U; /* R2  */
    *(--sp) = 0x00000001U; /* R1  */
    *(--sp) = 0x00000000U; /* R0  */
    /* additionally, fake registers R4-R11 */
    *(--sp) = 0x0000000BU; /* R11 */
    *(--sp) = 0x0000000AU; /* R10 */
    *(--sp) = 0x00000009U; /* R9 */
    *(--sp) = 0x00000008U; /* R8 */
    *(--sp) = 0x00000007U; /* R7 */
    *(--sp) = 0x00000006U; /* R6 */
    *(--sp) = 0x00000005U; /* R5 */
    *(--sp) = 0x00000004U; /* R4 */

	//save the top of the stack in the thread's attribute
	me->sp = sp;
	
	// rest of the stack with some recognizable pattern
	stk_limit = (uint32_t*)(((((uint32_t)stkSto - 1u) / 8) + 1u) * 8);
	
	for (sp = sp - 1u; sp >= stk_limit; --sp){
		*sp = 0xdeadbeefu;
	}

	/* register the thread with the OS */
	OS_thread[prio] = me;
	
	/* make thread ready to run */
	if (prio > 0u) {
		OS_readySet |= (1u << (prio - 1u));
	}
}

__asm
void PendSV_Handler(void) {
	IMPORT OS_curr
	IMPORT OS_next
	
	/*__disable_irq(); */
	CPSID         I

	 /* if (OS_curr != (OSThread *)0) { */
	LDR           r1,=OS_curr
	LDR           r1,[r1,#0x00]
	CBZ           r1,PendSV_restore
	
	/* push registers on the stack */
	PUSH					{r4-r11}
	
	/*  OS_curr-> sp = sp; */ 
	LDR           r1,=OS_curr
	LDR						r1,[r1,#0x00]
	STR           sp,[r1,#0x00]
	/* } */
	
PendSV_restore
	
	/*  sp = OS_next->sp; */
	LDR           r1,=OS_next
	LDR           r1,[r1,#0x00]
	LDR           sp,[r1,#0x00]		
	
	/*  OS_curr = OS_next; */ 
	LDR						r1,=OS_next
	LDR						r1,[r1, #0x00]
	LDR						r2,=OS_curr
	STR						r1,[r2, #0x00]
	
	/* pop registers r4-r11*/
	POP 					{r4-r11}
	
	/*     __enable_irq();  */
	CPSIE         I
	
	/* return to the next thread */
	BX						lr		
}
