/*
 * shal_systick_irq.h
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#ifndef SHAL_SYSTICK_IRQ_H_
#define SHAL_SYSTICK_IRQ_H_

#include "shal_systick.h"

typedef struct
{
	SHalSystickCallbackFn 	function;
	void 					*callbackUserParam;

} SHalSystickCallback;

typedef struct
{
	SHalSystickCallback callback[SHAL_SYSTICK_NUM_OF_CALLBACKS];

} SHalSystickCallbacks;

#endif /* SHAL_SYSTICK_IRQ_H_ */
