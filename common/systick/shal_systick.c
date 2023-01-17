/*
 * shal_systick.c
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#include "shal_systick.h"
#include "shal_systick_def.h"

#define CpuCriticalVar()  uint8_t cpuSR

#define CpuEnterCritical()              \
  do {                                  \
    asm (                               \
    "MRS   R0, PRIMASK\n\t"             \
    "CPSID I\n\t"                       \
    "STRB R0, %[output]"                \
    : [output] "=m" (cpuSR) :: "r0");   \
  } while(0)

#define CpuExitCritical()               \
  do{                                   \
    asm (                               \
    "ldrb r0, %[input]\n\t"             \
    "msr PRIMASK,r0;\n\t"               \
    ::[input] "m" (cpuSR) : "r0");      \
  } while(0)


volatile SHalSystick gSystick = {0};
volatile uint64_t gSysTickMajor = 0;

int shal_systick_init ()
{
	gSysTickMajor = 0;

	// set load value for 1ms overflow
	SysTick->LOAD = (SystemCoreClock / 1000) - 1; // (168000 - 1) = 0x2903F,

	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 	// Set dvider as 1
					SysTick_CTRL_ENABLE_Msk |		// Enable the counter
					SysTick_CTRL_TICKINT_Msk;		// Enable exception request

	return 0;
}

uint64_t shal_systick_get_ticks()
{
	uint64_t major;

	// Disable interrupts to avoid a race condition with systick_handler
	CpuCriticalVar();
	CpuEnterCritical();

	// Read current systick value
	uint32_t minor = SysTick->VAL;

	// Check if there is any new systick tick event occured
	if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
	{
		// New event occurred, so systick value has changed drastically
		// Re-read the value
		minor = SysTick->VAL;

		// New event occurred but interrupts are disabled. So increase ms by one
		major = gSysTickMajor + SysTick->LOAD + 1;
	}
	else
	{
		major = gSysTickMajor;
	}

	// Enable interrupts
	CpuExitCritical();

	return major + (SysTick->LOAD - minor);
}

void shal_systick_set_callback (SHalSystickCallbackID 	callbackID,
								SHalSystickCallbackFn 	callback,
								void 					*userParam)
{
	gSystick.callback[callbackID].function 			= callback;
	gSystick.callback[callbackID].callbackUserParam = userParam;
}
