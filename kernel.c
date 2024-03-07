#include "kernel.h"


tcb_t g_tcbs[NUM_OF_THREAD];
tcb_t *g_current_pt = (void *)0;

uint32_t g_tcb_stack[NUM_OF_THREAD][STACKSIZE];

void osKernelInit(int i)
{
  g_tcbs[i].stackPt = &g_tcb_stack[i][STACKSIZE - 16]; // sp
  g_tcb_stack[i][STACKSIZE - 1] = (1U << 24);

  g_tcb_stack[i][STACKSIZE - 3] = 0xAAAAAAAAU; // r14
  g_tcb_stack[i][STACKSIZE - 4] = 0xAAAAAAAAU; // r12
  g_tcb_stack[i][STACKSIZE - 5] = 0xAAAAAAAAU; // r3
  g_tcb_stack[i][STACKSIZE - 6] = 0xAAAAAAAAU; // r2
  g_tcb_stack[i][STACKSIZE - 7] = 0xAAAAAAAAU; // r1
  g_tcb_stack[i][STACKSIZE - 8] = 0xAAAAAAAAU; // r0
  g_tcb_stack[i][STACKSIZE - 9] = 0xAAAAAAAAU; // r11
  g_tcb_stack[i][STACKSIZE - 10] = 0xAAAAAAAAU; // r10
  g_tcb_stack[i][STACKSIZE - 11] = 0xAAAAAAAAU; // r9
  g_tcb_stack[i][STACKSIZE - 12] = 0xAAAAAAAAU; // r8
  g_tcb_stack[i][STACKSIZE - 13] = 0xAAAAAAAAU; // r7
  g_tcb_stack[i][STACKSIZE - 14] = 0xAAAAAAAAU; // r6
  g_tcb_stack[i][STACKSIZE - 15] = 0xAAAAAAAAU; // r5
  g_tcb_stack[i][STACKSIZE - 16] = 0xAAAAAAAAU; // r4
}

int osKernelAddThread(task_func_t task0, task_func_t task1, task_func_t task2)
{
  __asm("cpsid i");
  //! round robin
  g_tcbs[0].next = &g_tcbs[1];
  g_tcbs[1].next = &g_tcbs[2];
  g_tcbs[2].next = &g_tcbs[0];

  //! initialize the stack
  osKernelInit(0);
  g_tcb_stack[0][STACKSIZE - 2] = (uint32_t)task0;
  osKernelInit(1);
  g_tcb_stack[1][STACKSIZE - 2] = (uint32_t)task1;
  osKernelInit(2);
  g_tcb_stack[2][STACKSIZE - 2] = (uint32_t)task2;
  g_current_pt = &g_tcbs[0];
  __asm("cpsie i");

  return 0;
}

