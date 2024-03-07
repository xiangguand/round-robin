#ifndef KERNEL_H_
#define KERNEL_H_

#include <stdint.h>

#define NUM_OF_THREAD (3)
#define STACKSIZE     (1024)


typedef struct _tcb_t
{
  uint32_t *stackPt;
  struct _tcb_t *next;
} tcb_t;

typedef void (*task_func_t)(void);

void osKernelInit(int i);
int osKernelAddThread(task_func_t task0, task_func_t task1, task_func_t task2);
extern void osKernelSchedulerLaunch(void);

#endif /* KERNEL_H */
