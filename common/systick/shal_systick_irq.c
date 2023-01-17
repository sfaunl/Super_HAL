/*
 * shal_systick_irq.c
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#include "shal_systick.h"
#include "shal_systick_irq.h"
#include "shal_systick_def.h"

extern SHalSystick gSystick;
extern volatile uint64_t gSysTickMajor;

void SysTick_Handler(void)
{
	__disable_irq();
	// Increase milliseconds
	gSystick.systick_ms += 1;
	gSysTickMajor += SysTick->LOAD + 1;

	// Reset COUNTFLAG by reading SysTick->CTRL register
	// TODO: This line might get ignored if compiler optimizer is on
	SysTick->CTRL;
	__enable_irq();

	// Call user callback
	if (gSystick.callback[SHAL_SYSTICK_CALLBACK_RELOAD].function)
	{
		gSystick.callback[SHAL_SYSTICK_CALLBACK_RELOAD].function
		(gSystick.callback[SHAL_SYSTICK_CALLBACK_RELOAD].callbackUserParam);
	}
}
