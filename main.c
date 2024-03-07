#include <stdint.h>
#include <stdio.h>
#include "stm32f7xx.h"                  // Device header
#include "kernel.h"

int cnt0 = 0;
int cnt1 = 0;
int cnt2 = 0;


void task0(void)
{
	while(1)
	{
		cnt0++;
		__asm("nop");
	}
}
void task1(void)
{
	while(1)
	{
		cnt1++;
		__asm("nop");
	}
}
void task2(void)
{
	while(1)
	{
		cnt2++;
		__asm("nop");
	}
}

void callStackTest(int a, int *b)
{
	int buf[100];
	if(a < 3)
	{
		for(int i=0;i<100;i++)
		{
			buf[i] = i;
		}
		for(int i=0;i<100;i++)
		{
			*b += buf[i];
		}
	}
	else
	{
		return;
	}
	callStackTest(a+1, b);
}

int main()
{
	/*
	osKernelAddThread(task0, task1, task2);
	NVIC_SetPriority(SysTick_IRQn, 15);
	SysTick_Config(SystemCoreClock / 1000);
	NVIC_EnableIRQ(SysTick_IRQn);

	osKernelSchedulerLaunch();
	*/

	int t = 0;
	callStackTest(0, &t);
	
	printf("Hello: %d\n", t);
	
	while(1)
	{
		__asm("nop");
	}
}

