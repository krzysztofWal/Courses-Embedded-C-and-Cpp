#include <stdint.h>
#include "miros.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

OSThread * volatile OS_curr; // pointer to current thread //used inside interrupts
OSThread * volatile OS_next; // pointer to the next thread to run

OSThread *OS_thread[32 + 1]; /* array of threads started*/
uint8_t OS_threadNum;
uint8_t OS_currIdx;
uint32_t OS_readySet; /* bitmask of threads that are ready to run */

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
	OSThread_start(&idleThread,
					&main_idleThread,
					stkSto, stkSize);
	
}

void OS_sched(void) {
		
	/* OS_next = ... */
	
	if (OS_readySet == 0U)  {/* idle condition */
		OS_currIdx = 0u;
	} else {
		do { // advance currIdx until the corresponding bit in a mask is 1 - that is the thread is ready
			++OS_currIdx;
			if (OS_currIdx == OS_threadNum) {
				OS_currIdx = 1u; // first thread is idle (first that is the 0 index)
			}
		} while ((OS_readySet & (1u << (OS_currIdx - 1u))) == 0u);
	}
	OS_next = OS_thread[OS_currIdx];

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
	uint8_t n;
	for (n = 1u; n < OS_threadNum; n++) {
		if (OS_thread[n]->timeout != 0u) {
			--OS_thread[n]->timeout; //timeout change is impossible in the OS_tick as it is used in interrupts, and any change to it can happen in OS_delay() tha is called from the threads
			if (OS_thread[n]->timeout == 0u) {
				OS_readySet |= (1u << (n - 1u)); // thread n is ready to run - setting 
			}
		}
	}
}

void OS_delay(uint32_t ticks) {
	__disable_irq();
	
	/* never call OS_delay from the idleThread */
	Q_REQUIRE(OS_curr != OS_thread[0]);
	
	OS_curr->timeout = ticks;
	OS_readySet &= ~(1u << (OS_currIdx - 1u)); /* set corresponding bit in readySet bitmask to 0 - thread is not ready to run*/
	OS_sched();
	__enable_irq();
}

void OSThread_start(
	OSThread *me, //a pointer to the TCB
	OSThreadHandler threadHandler, 
	void *stkSto, uint32_t stkSize)
{
	uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8) * 8); //rounding to the top of 8th byte boundary
	uint32_t *stk_limit;

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
	
	Q_ASSERT(OS_threadNum < Q_DIM(OS_thread));
		
	/* register the thread with the OS */
	OS_thread[OS_threadNum] = me;
	
	/* make thread ready to run */
	if (OS_threadNum > 0u) {
		OS_readySet |= (1u << (OS_threadNum - 1u));
	}
	++OS_threadNum;
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
