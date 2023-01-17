/*
 * shal_time.c
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#include "shal_time.h"
#include "systick/shal_systick.h"

uint32_t gDelayusCalib = 0;
uint32_t gGetnsCalib = 0;

void shal_time_init()
{
	// Initialize systick
	shal_systick_init();

	// Calculate function read times for calibration
	uint64_t lTime[2];

	lTime[0] = shal_time_get_ns();
	lTime[1] = shal_time_get_ns();
	gGetnsCalib = lTime[1] - lTime[0];

	// Calibration iteration 1
	lTime[0] = shal_time_get_ns();
	shal_time_delay_us(10);
	lTime[1] = shal_time_get_ns();
	gDelayusCalib = lTime[1] - lTime[0] - 10000;

	// Calibration iteration 2
	lTime[0] = shal_time_get_ns();
	shal_time_delay_us(10);
	lTime[1] = shal_time_get_ns();
	gDelayusCalib = lTime[1] - lTime[0] - 10000;

	// Add shal_time_get_uptime_ns function delay
	gDelayusCalib += gGetnsCalib;
}

// return type uint64_t: 2^64 * 1ns = 213 503 d + 23 h + 34 min + 33.709552 s
// return type uint32_t: 2^32 * 1ns = 4.2949673 seconds!!
uint64_t shal_time_get_ns()
{
	uint64_t ticks = shal_systick_get_ticks();

	// Calculate nanoseconds and return
    return ticks * (1e9 / SystemCoreClock);
}

// return type 64: 2^64 * 1us = 213 503 982 d + 8 h + 1 min + 49.551616 s
// return type 32: 2^32 * 1us = 1 h + 11 min + 34.967296 s
uint64_t shal_time_get_us()
{
	uint64_t ticks = shal_systick_get_ticks();

	// Calculate microseconds and return
    return ((ticks * 1e6) / SystemCoreClock);
}

// TODO: Overflow will occur after 49days. Change to uint64?
// return type 32: 2^32 × 1ms = 49 d + 17 h + 2 min + 47.296 s
uint32_t shal_time_get_ms()
{
	uint64_t ticks = shal_systick_get_ticks();

	// Calculate milliseconds and return
    return (uint32_t)((ticks * 1e3) / SystemCoreClock);
}

void shal_time_delay_us(uint32_t value)
{
	value *= 1000;
	uint64_t startTime = shal_time_get_ns();
	while ((shal_time_get_ns() - startTime) + gDelayusCalib < value);
}
