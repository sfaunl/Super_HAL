/*
 * shal_stm32h7_gpio.h
 *
 *  Created on: Jan 17, 2023
 *      Author: sef
 */

#ifndef SHAL_STM32H7_GPIO_H_
#define SHAL_STM32H7_GPIO_H_

#include "shal_stm32h7_gpio_def.h"

#ifdef STM32H7

void shal_gpio_set_as_analog 				(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin);

void shal_gpio_set_as_alternate_function 	(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin,
											 SHAL_GPIO_AF alternateFunction,
											 SHAL_GPIO_OTYPE outputType,
											 SHAL_GPIO_OSPEED outputSpeed,
											 SHAL_GPIO_PULLUPDOWN pullUpDown);

void shal_gpio_set_as_output 				(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin,
											 SHAL_GPIO_OTYPE outputType,
											 SHAL_GPIO_OSPEED outputSpeed,
											 SHAL_GPIO_PULLUPDOWN pullUpDown);

void shal_gpio_set_as_input 				(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin,
											 SHAL_GPIO_PULLUPDOWN pullUpDown);

static inline void shal_gpio_set (GPIO_TypeDef *GPIOx, uint16_t GPIO_pins)
{
	GPIOx->BSRR = GPIO_pins;
}

static inline void shal_gpio_reset (GPIO_TypeDef *GPIOx, uint32_t GPIO_pins)
{
	GPIOx->BSRR = GPIO_pins << 16;
}

static inline void shal_gpio_toggle (GPIO_TypeDef *GPIOx, uint32_t GPIO_pin)
{
	if ((GPIOx->ODR & GPIO_pin) == GPIO_pin)
	{
		// Reset
		GPIOx->BSRR = GPIO_pin << 16;
	}
	else
	{
		// Set
		GPIOx->BSRR = GPIO_pin;
	}
}

static inline void shal_gpio_toggle2 (GPIO_TypeDef *GPIOx, uint32_t GPIO_pins)
{
	// Reset
	GPIOx->BSRR = (GPIO_pins & GPIOx->ODR) << 16;

	// Set
	GPIOx->BSRR = (GPIO_pins & (~(GPIOx->ODR)));
}

static inline void shal_gpio_write (GPIO_TypeDef *GPIOx, uint32_t GPIO_pins, uint32_t state)
{
	if (state)
	{
		// Set
		GPIOx->BSRR = GPIO_pins;
	}
	else
	{
		// Reset
		GPIOx->BSRR = GPIO_pins << 16;
	}
}

static inline uint8_t shal_gpio_read (GPIO_TypeDef *GPIOx, uint16_t GPIO_pin)
{
	return ((GPIOx->ODR & GPIO_pin) == GPIO_pin);
}

static inline void shal_gpio_set_pullupdown(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin, SHAL_GPIO_PULLUPDOWN pullUpDown)
{
	GPIOx->PUPDR &= ~(GPIO_pin * GPIO_pin * GPIO_PUPDR_PUPD0); 	// clear mask
	GPIOx->PUPDR |= GPIO_pin * GPIO_pin * pullUpDown; 			// set mask
}

static inline void shal_gpio_set_speed(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin, SHAL_GPIO_OSPEED outputSpeed)
{
	GPIOx->OSPEEDR &= ~(GPIO_pin * GPIO_pin * GPIO_OSPEEDR_OSPEED0); 	// clear mask
	GPIOx->OSPEEDR |= GPIO_pin * GPIO_pin * outputSpeed; 				// set mask
}

static inline void shal_gpio_set_output_type(GPIO_TypeDef *GPIOx, uint16_t GPIO_pins, SHAL_GPIO_OTYPE outputType)
{
	GPIOx->OTYPER &= ~(GPIO_pins); 				// clear mask
	GPIOx->OTYPER |= GPIO_pins * outputType; 	// set mask
}

static inline void shal_gpio_set_mode(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin, SHAL_GPIO_MODE mode)
{
	GPIOx->MODER &= ~(GPIO_pin * GPIO_pin * GPIO_MODER_MODE0); 	// clear mask
	GPIOx->MODER |= GPIO_pin * GPIO_pin * mode; 				// set mask
}

static inline void shal_gpio_set_alternate_function(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin, SHAL_GPIO_AF alternateFunction)
{
	if (GPIO_pin < 256) // GPIO pin 0-7
	{
		GPIOx->AFR[0] &= ~(GPIO_pin * GPIO_pin * GPIO_pin * GPIO_pin * GPIO_AFRL_AFSEL0_Msk); 	// clear mask
		GPIOx->AFR[0] |= GPIO_pin * GPIO_pin * GPIO_pin * GPIO_pin * alternateFunction; 		// set mask
	}
	else  // GPIO pin 8-15
	{
		GPIO_pin = GPIO_pin >> 8;
		GPIOx->AFR[1] &= ~(GPIO_pin * GPIO_pin * GPIO_pin * GPIO_pin * GPIO_AFRL_AFSEL0_Msk); 	// clear mask
		GPIOx->AFR[1] |= GPIO_pin * GPIO_pin * GPIO_pin * GPIO_pin * alternateFunction; 		// set mask
	}
}
#endif // STM32H7

#endif /* SHAL_STM32H7_GPIO_H_ */
