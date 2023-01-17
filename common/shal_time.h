/*
 * shal_time.h
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#ifndef SHAL_TIME_H_
#define SHAL_TIME_H_

#include "../shal.h"

typedef struct _SHalTime
{
	uint64_t ms;
	uint32_t ns;

} SHalTime;

void 		shal_time_init ();

uint32_t 	shal_time_get_ms ();
uint64_t 	shal_time_get_us ();
uint64_t 	shal_time_get_ns ();

void 		shal_time_delay_us(uint32_t value);

#endif /* SHAL_TIME_H_ */
