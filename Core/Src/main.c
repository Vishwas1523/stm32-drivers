#include "stm32f446xx.h"
#include "hal_gpio.h"
#include "uart_debug.h"
#include "adc.h"
#include "uart.h"
#include "HAL_DMA.h"


int main(void){

	DMA2_CLOCK_EN;

	DMA_HandlerTypeDef hdma1 = {0};
	hdma1.controller = DMA_2;
	hdma1.instance = DMA2_Stream_0;
	hdma1.config.channel = DMA_CHANNEL0;
	hdma1.config.priority = DMA_PRIORITY_VERY_HIGH;
	hdma1.config.direction = DMA_DIRECTION_MEM_TO_MEM;
	hdma1.config.fifoMode = DMA_FIFO_FULL;
	hdma1.config.MSIZE = DMA_DATA_SIZE_WORD;
	hdma1.config.PSIZE = DMA_DATA_SIZE_WORD;
	hdma1.config.peripheralIncrementMode = DMA_ENABLE;
	hdma1.config.memoryIncrementMode = DMA_ENABLE;

	uint32_t buff[10] = {29, 22, 43, 7, 18, 45, 66, 49, 1, 32};
	uint32_t dst[10] = {0};

	//number of transfers is 0x28 or 40 in decimal because MSIZE and PSIZE is 32 bit.
	//and for 32bit integers memory increment is 4 times of the actual number of transactions.
	DMA_Start(&hdma1, (uint32_t)&buff, (uint32_t)&dst, 0x28);
	uart_init();
	UART_printf("\r\n-----------------------------------------");
	for(int i = 0; i < 10; i++) UART_printf("\r\n%d", dst[i]);
    while (1){

    }
}


