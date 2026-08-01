/*
 * HAL_DMA.c
 *
 *  Created on: Jul 29, 2026
 *      Author: VICTUS
 */
#include "HAL_DMA.h"


inline void DMA_DeInit(DMA_HandlerTypeDef* hdma){
	hdma->instance->CR &= ~DMA_CR_EN;
}

void DMA_Init(DMA_HandlerTypeDef* hdma){
	DMA_DeInit(hdma);
	hdma->instance->CR |= hdma->config.channel		<< 	DMA_CR_CHSEL_Pos;
	hdma->instance->CR |= hdma->config.priority		<<	DMA_CR_PL_Pos;
	hdma->instance->CR |= hdma->config.direction	<< 	DMA_CR_DIR_Pos;
	hdma->instance->CR |= hdma->config.peripheralIncrementMode	<< DMA_CR_PINC_Pos;
	hdma->instance->CR |= hdma->config.memoryIncrementMode    <<  DMA_CR_MINC_Pos;
	hdma->instance->CR |= hdma->config.circularMode	<< DMA_CR_CIRC_Pos;
	hdma->instance->CR |= hdma->config.PSIZE << DMA_CR_PSIZE_Pos;
	hdma->instance->CR |= hdma->config.MSIZE << DMA_CR_MSIZE_Pos;
}


