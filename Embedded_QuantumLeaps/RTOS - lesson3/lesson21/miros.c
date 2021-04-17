#include <stdint.h>
#include "miros.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

OSThread * volatile OS_curr; // pointer to current thread //used inside interrupts
OSThread * volatile OS_next; // pointer to the next thread to run

OSThread *OS_thread[32 + 1]; /* array of threads started*/
uint8_t OS_threadNum;
uint8_t OS_currIdx;


void OS_init(void) {
		// setting the Pend SV interrupt priority to the lowest level
		*(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);
		
}

void OS_sched(void) {
		
//		extern OSThread blinky1;
//		extern OSThread blinky2;	
//	
//		/* QS_next = ... */
//		
//		if (OS_curr == &blinky1){
//				OS_next = &blinky2;
//		} else {
//				OS_next = &blinky1;
//		}
		++OS_currIdx;
		if (OS_currIdx == OS_threadNum) {
				OS_currIdx = 0u;
		}
		
		OS_next = OS_thread[OS_currIdx];
	
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
		++OS_threadNum;
}

__asm
void PendSV_Handler(void) {
			
//		void *sp;
//		__disable_irq();
//		/* save stack content of the current thread */
//		/* check if any thread is running, if not OS_Curr will be empty*/
//		if (OS_curr != (OSThread *)0) {
//				/* push registers r4-r11 on the stack ("save" their state so we will go back to the thread with proper register values)*/
//				OS_curr-> sp = sp; /* saving the stack pointer content of the thread we're leaving*/
//		}
//		/* set SP register to the pointer of the structure representing the thread we're going into*/
//		sp = OS_next->sp;
//		/* changing current thread */
//		OS_curr = OS_next;
//		/* pop registers of current thread onto stack (as they were when we've last left the new current thread)*/
//		__enable_irq();
	
	
// it doesn't work for some reason
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

		
//		IMPORT  OS_curr  /* extern variable */
//    IMPORT  OS_next  /* extern variable */
//   
//    /* __disable_irq(); */
//    CPSID         I

//    /* if (OS_curr != (OSThread *)0) { */ 
//    LDR           r1,=OS_curr
//    LDR           r1,[r1,#0x00]
//    CBZ           r1,PendSV_restore

//    /*     push registers r4-r11 on the stack */
//    PUSH          {r4-r11}    

//    /*     OS_curr->sp = sp; */ 
//    LDR           r1,=OS_curr
//    LDR           r1,[r1,#0x00]
//    STR           sp,[r1,#0x00]
//    /* } */

//PendSV_restore    
//    /* sp = OS_next->sp; */
//    LDR           r1,=OS_next
//    LDR           r1,[r1,#0x00]
//    LDR           sp,[r1,#0x00]

//    /* OS_curr = OS_next; */
//    LDR           r1,=OS_next
//    LDR           r1,[r1,#0x00]
//    LDR           r2,=OS_curr
//    STR           r1,[r2,#0x00]

//    /* pop registers r4-r11 */ 
//    POP           {r4-r11}    

//    /* __enable_irq(); */
//    CPSIE         I

//    /* return to the next thread */
//    BX            lr    
}


