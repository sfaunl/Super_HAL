/*
 * shal_stm32h7_gpio.c
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
*/

#include "stdint.h"
#include "../shal_stm32h7.h"

#include "shal_stm32h7_gpio.h"

#ifdef STM32H7

static void gpio_enable_peripheral_clk(GPIO_TypeDef *GPIOx)
{
	RCC->AHB4ENR |= (1 << (((uint32_t)GPIOx - D3_AHB1PERIPH_BASE) >> 10));
}

void shal_gpio_set_as_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin,
							SHAL_GPIO_PULLUPDOWN pullUpDown)
{
	gpio_enable_peripheral_clk(GPIOx);

	shal_gpio_set_mode 		(GPIOx, GPIO_pin, SHAL_GPIO_MODE_INPUT);
	shal_gpio_set_pullupdown(GPIOx, GPIO_pin, pullUpDown);
}

void shal_gpio_set_as_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin,
							 SHAL_GPIO_OTYPE outputType, SHAL_GPIO_OSPEED outputSpeed, SHAL_GPIO_PULLUPDOWN pullUpDown)
{
	gpio_enable_peripheral_clk(GPIOx);

	shal_gpio_set_mode 				(GPIOx, GPIO_pin, SHAL_GPIO_MODE_OUTPUT);
	shal_gpio_set_alternate_function(GPIOx, GPIO_pin, SHAL_GPIO_AF_0);
	shal_gpio_set_pullupdown 		(GPIOx, GPIO_pin, pullUpDown);
	shal_gpio_set_speed 			(GPIOx, GPIO_pin, outputSpeed);
	shal_gpio_set_output_type 		(GPIOx, GPIO_pin, outputType);
}

void shal_gpio_set_as_alternate_function(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin, SHAL_GPIO_AF alternateFunction,
										 SHAL_GPIO_OTYPE outputType, SHAL_GPIO_OSPEED outputSpeed, SHAL_GPIO_PULLUPDOWN pullUpDown)
{
	gpio_enable_peripheral_clk(GPIOx);

	shal_gpio_set_alternate_function(GPIOx, GPIO_pin, alternateFunction);
	shal_gpio_set_mode 				(GPIOx, GPIO_pin, SHAL_GPIO_MODE_ALTERNATE);
	shal_gpio_set_pullupdown 		(GPIOx, GPIO_pin, pullUpDown);
	shal_gpio_set_speed 			(GPIOx, GPIO_pin, outputSpeed);
	shal_gpio_set_output_type 		(GPIOx, GPIO_pin, outputType);
}

void shal_gpio_set_as_analog(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin)
{
	gpio_enable_peripheral_clk(GPIOx);

	shal_gpio_set_mode(GPIOx, GPIO_pin, SHAL_GPIO_MODE_ANALOG);
}

#endif // STM32H7
