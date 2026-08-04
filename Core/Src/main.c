#include "stm32f446xx.h"
#include "hal_gpio.h"
#include "uart_debug.h"
#include "adc.h"
#include "uart.h"
#include "HAL_DMA.h"

#include <string.h>
int main(void){

	DMA1_CLOCK_EN;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIO_Type MyGPIO;
    MyGPIO.GPIO = GPIOA;
    MyGPIO.Mode = AF_MODE;
    MyGPIO.Output_Speed = FAST_SPEED;
    MyGPIO.Output_Type = PUSH_PULL;
    MyGPIO.PullUp_PullDown = NO_PULLUP_PULLDOWN;
	MyGPIO.pin_number = 2;
	MyGPIO.alternate_function  = 7;

	GPIO_Init(MyGPIO);

	UART_HandlerTypeDef_t huart1;

    huart1.instance = USART2;
    huart1.config.baudRate = UART_BAUD_9600;
    huart1.config.wordLength = UART_8_BIT_DATA;
    huart1.config.stopBits = UART_1_STOP_BIT;
    huart1.config.transmitEnable = UART_ENABLE;
    huart1.config.recieveEnable = UART_DISABLE;
    UART_Init(&huart1);

	DMA_HandlerTypeDef hdma1 = {0};
	hdma1.controller = DMA_1;
	hdma1.instance = DMA1_Stream_6;
	hdma1.config.channel = DMA_CHANNEL4;
	hdma1.config.priority = DMA_PRIORITY_VERY_HIGH;
	hdma1.config.direction = DMA_DIRECTION_MEM_TO_PER;
	hdma1.config.fifoMode = DMA_FIFO_FULL;
	hdma1.config.MSIZE = DMA_DATA_SIZE_BYTE;
	hdma1.config.PSIZE = DMA_DATA_SIZE_BYTE;
	hdma1.config.peripheralIncrementMode = DMA_DISABLE;
	hdma1.config.memoryIncrementMode = DMA_ENABLE;

	huart1.instance->CR3 |= USART_CR3_DMAT;

	char buff[] = "\r\nHello World!";
	DMA_Start(&hdma1, (uint32_t)&buff, (uint32_t)&huart1.instance->DR, 14);

    while (1){

    }
}


