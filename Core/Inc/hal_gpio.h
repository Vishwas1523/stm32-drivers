/*
 * hal_gpio.h
 *
 *  Created on: May 16, 2026
 *      Author: VICTUS
 */

#ifndef INC_HAL_GPIO_H_
#define INC_HAL_GPIO_H_
#include "stm32f446xx.h"
#include <stdint.h>

//input/output value
#define HIGH	1
#define LOW		0


//clock enables
#define GPIOA_CLOCK_ENABLE_		(RCC->AHB1ENR |= (1<<0));
#define GPIOB_CLOCK_ENABLE_		(RCC->AHB1ENR |= (1<<1));
#define GPIOC_CLOCK_ENABLE_		(RCC->AHB1ENR |= (1<<2));
#define GPIOD_CLOCK_ENABLE_		(RCC->AHB1ENR |= (1<<3));


//mode types
#define INPUT_MODE		(uint32_t)0x00
#define	OUTPUT_MODE		(uint32_t)0x01
#define AF_MODE			(uint32_t)0x02
#define ANALOG_MODE		(uint32_t)0x03


//output types
#define PUSH_PULL		(uint32_t)0x00
#define OPEN_DRAIN		(uint32_t)0x01


//output speed
#define LOW_SPEED			(uint32_t)0x00
#define MEDIUM_SPEED		(uint32_t)0x01
#define FAST_SPEED			(uint32_t)0x02
#define HIGH_SPEED			(uint32_t)0x03


//pull-up, pull-down information
#define NO_PULLUP_PULLDOWN		(uint32_t)0x00
#define PULLUP					(uint32_t)0x01
#define PULLDOWN				(uint32_t)0x02


//AF modes
#define AF0			 0U
#define AF1			 1U
#define AF2			 2U
#define AF3	 		 3U
#define AF4	 		 4U
#define AF5	 		 5U
#define AF6			 6U
#define AF7			 7U
#define AF8			 8U
#define AF9			 9U
#define AF10		10U
#define AF11		11U
#define AF12		12U
#define AF13		13U
#define AF14		14U
#define AF15		15U

//structure to access the registers and modes
typedef struct{
	GPIO_TypeDef* GPIO;
	uint32_t Mode;
	uint32_t Output_Type;
	uint32_t Output_Speed;
	uint32_t PullUp_PullDown;
	uint8_t pin_number;
	uint8_t alternate_function;
}GPIO_Type;


//enum to define edges for the interrupts
typedef enum{
	RISING_EDGE = 0,
	FALLING_EDGE,
	RISING_AND_FALLING_EDGE
}edge_t;


//gpio functions
void GPIO_config(GPIO_TypeDef* GPIO, uint32_t Mode, uint8_t pin_number);
void GPIO_Input_Config(GPIO_TypeDef* GPIO, uint32_t PullUp_PullDown, uint8_t pin_number);
void GPIO_Output_Config(GPIO_TypeDef* GPIO, uint32_t Output_Type, uint32_t Output_Speed, uint32_t PullUp_PullDown, uint8_t pin_number);
void GPIO_AF_Config(GPIO_TypeDef* GPIO, uint8_t pin_number, uint8_t alternate_function, uint32_t Output_Type, uint32_t Output_Speed, uint32_t PullUp_PullDown);
uint8_t GPIO_Read(GPIO_TypeDef* GPIO, uint8_t pin_number);
void GPIO_Write(GPIO_TypeDef* GPIO, uint8_t pin_number, uint8_t output_value);
void GPIO_Toggle_Pin(GPIO_TypeDef* GPIO, uint8_t pin_number);
void GPIO_Init(GPIO_Type MyGPIO);


//interrupt functions
void GPIO_Interrupt_Config(GPIO_TypeDef* GPIO, uint8_t pin_number, edge_t edge);
void GPIO_Interrupt_Enable(uint8_t pin_number, IRQn_Type IRQ_Number);
void GPIO_Interrupt_Clear(uint8_t pin_number);









#endif /* INC_HAL_GPIO_H_ */
