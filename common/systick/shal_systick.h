/*
 * shal_systick.h
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#ifndef SHAL_SYSTICK_H_
#define SHAL_SYSTICK_H_

#include "../../shal.h"

// TODO: Remove these defines and get them from shal_rcc functions
#define CPU_FREQUENCY 		(SystemCoreClock)
#define CPU_FREQUENCY_MHZ 	((CPU_FREQUENCY) / 1000000)
#define CPU_CLOCK_PERIOD 	(1.0 / (CPU_FREQUENCY))

typedef void (*SHalSystickCallbackFn)(void *userParam);

typedef enum
{
	SHAL_SYSTICK_CALLBACK_RELOAD,	// Callback for systick reload event
	SHAL_SYSTICK_NUM_OF_CALLBACKS

} SHalSystickCallbackID;

/** @brief Initializes the SysTick to create an event every 1ms
 *
 * @return Returns 0 on success
 */
int shal_systick_init ();

/**
 *
 * @return
 */
uint64_t shal_systick_get_ticks ();

/**
 *
 * @param callbackID
 * @param callback
 * @param userParam
 */
void shal_systick_set_callback (SHalSystickCallbackID 	callbackID,
								SHalSystickCallbackFn 	callback,
								void 					*userParam);

#endif /* SHAL_SYSTICK_H_ */
