	#include "stm32f446xx.h"
	#include "hal_gpio.h"
	#include "uart_debug.h"
	#include "adc.h"
	#include "uart.h"
	#include "HAL_DMA.h"

	#include <string.h>
	int main(void){

//		DMA1_CLOCK_EN;
//		DMA2_CLOCK_EN;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
//		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

		GPIO_Type MyGPIO;
		MyGPIO.GPIO = GPIOA;
		MyGPIO.Mode = OUTPUT_MODE;
		MyGPIO.Output_Speed = FAST_SPEED;
		MyGPIO.Output_Type = PUSH_PULL;
		MyGPIO.PullUp_PullDown = NO_PULLUP_PULLDOWN;
		MyGPIO.pin_number = 5;
//		MyGPIO.alternate_function  = 7;

		GPIO_Init(MyGPIO);
		GPIO_Write(GPIOA, 5, HIGH);
		while (1){

		}
		return 0;
	}


