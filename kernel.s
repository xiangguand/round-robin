
	.global SysTick_Handler
	.global osKernelSchedulerLaunch
	.global g_current_pt
	.align 4	
	.text
	.type SysTick_Handler, %function
	.type osKernelSchedulerLaunch, %function

SysTick_Handler:
	cpsid i
	push {r4-r11}
	ldr r0, =g_current_pt
	ldr r1, [r0]
	str sp, [r1]
	ldr r1, [r1, #4]
	str r1, [r0]
	ldr sp, [r1]
	pop {r4-r11}
	cpsie i
	bx lr
	
osKernelSchedulerLaunch:
	cpsid i
	ldr r0, =g_current_pt
	ldr r2, [r0]
	ldr sp, [r2]
	pop {r4-r11}
	pop {r12}
	pop {r0-r3}
	add sp, sp, #4
	pop {lr}
	add sp, sp, #4
	cpsie i
	bx lr

