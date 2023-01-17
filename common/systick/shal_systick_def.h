/*
 * shal_systick_def.h
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#ifndef SHAL_SYSTICK_DEF_H_
#define SHAL_SYSTICK_DEF_H_

#include "shal_systick_irq.h"

typedef struct
{
	SHalSystickCallback	callback[SHAL_SYSTICK_NUM_OF_CALLBACKS];
	uint32_t 			systick_ms;

} SHalSystick;

#endif /* SHAL_SYSTICK_DEF_H_ */
