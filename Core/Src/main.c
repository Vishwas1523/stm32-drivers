#include "stm32f446xx.h"
#include "hal_gpio.h"
#include "uart_debug.h"
#include "adc.h"
#include "uart.h"
#include "HAL_DMA.h"

#include <string.h>
int main(void){

	DMA1_CLOCK_EN;
	DMA2_CLOCK_EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    GPIO_Type MyGPIO;
    MyGPIO.GPIO = GPIOA;
    MyGPIO.Mode = AF_MODE;
    MyGPIO.Output_Speed = FAST_SPEED;
    MyGPIO.Output_Type = PUSH_PULL;
    MyGPIO.PullUp_PullDown = NO_PULLUP_PULLDOWN;
	MyGPIO.pin_number = 2;
	MyGPIO.alternate_function  = 7;

	GPIO_Init(MyGPIO);

	GPIO_Type MyGPIO2;
	MyGPIO2.GPIO = GPIOA;
    MyGPIO2.Mode = ANALOG_MODE;
    MyGPIO2.Output_Speed = FAST_SPEED;
    MyGPIO2.Output_Type = PUSH_PULL;
    MyGPIO2.PullUp_PullDown = NO_PULLUP_PULLDOWN;
	MyGPIO2.pin_number = 0;

	GPIO_Init(MyGPIO2);

	ADC_HandleTypeDef hadc1 = {0};
	hadc1.instance = ADC1;
	hadc1.config.resolution = ADC_RESOLUTION_12_BITS;
	hadc1.config.channels[0].channel = ADC_CHANNEL_0;
	hadc1.config.channels[0].samplingTime = ADC_SAMPLING_CYCLES_480;
	hadc1.config.alignment = ADC_RIGHT_ALIGNMENT;
	hadc1.config.scanMode = ADC_ENABLE;
	hadc1.config.continuousMode = ADC_DISABLE;
	hadc1.config.dmaMode = ADC_ENABLE;
	hadc1.config.trigger = ADC_TRIGGER_SOFTWARE;
	hadc1.config.edge = ADC_RISING_EDGE;
	hadc1.config.numConversions = 8;
	hadc1.config.eocSelection = ADC_EOC_EACH_CONVERSION;
	ADC_Init(&hadc1);
	ADC_Start(&hadc1);

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
	hdma1.config.MSIZE = DMA_DATA_SIZE_HALF_WORD;
	hdma1.config.PSIZE = DMA_DATA_SIZE_HALF_WORD;
	hdma1.config.peripheralIncrementMode = DMA_DISABLE;
	hdma1.config.memoryIncrementMode = DMA_ENABLE;

	huart1.instance->CR3 |= USART_CR3_DMAT;

	DMA_HandlerTypeDef hdma2 = {0};
	hdma1.controller = DMA_2;
	hdma1.instance = DMA1_Stream_0;
	hdma1.config.channel = DMA_CHANNEL0;
	hdma1.config.priority = DMA_PRIORITY_VERY_HIGH;
	hdma1.config.direction = DMA_DIRECTION_PER_TO_MEM;
	hdma1.config.directModeDisable = DMA_DISABLE;
	hdma1.config.MSIZE = DMA_DATA_SIZE_HALF_WORD;
	hdma1.config.PSIZE = DMA_DATA_SIZE_HALF_WORD;
	hdma1.config.peripheralIncrementMode = DMA_DISABLE;
	hdma1.config.memoryIncrementMode = DMA_ENABLE;

	uint16_t buff[8] = {0};
	DMA_Start(&hdma2, (uint32_t)&hadc1.instance->DR, (uint32_t)&buff, 16);


    while (1){

    }
}


