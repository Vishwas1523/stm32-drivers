
#ifndef INC_HAL_DMA_H_
#define INC_HAL_DMA_H_

#include <stdint.h>


typedef struct{
	volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
	volatile uint32_t M0AR;
	volatile uint32_t M1AR;
	volatile uint32_t FCR;
}DMA_Stream_TypeDef;

typedef enum{
	DMA_DISABLE = 0,
	DMA_ENABLE = 1
}DMA_FunctionalState_t;


typedef enum{
	P_to_P = 0,
	M_to_P = 1,
	M_to_M = 2
}DMA_Direction_t;

typedef enum{
	BYTE = 0,
	HALF_WORD = 1,
	WORD = 2
}DMA_Size_t;

typedef enum{
	LOw = 0,
	MEDIUM = 1,
	HIGH = 2,
	VERY_HIGH = 3
}DMA_Priority_t;

typedef enum{
	CHANNEL0 = 0,
	CHANNEL1 = 1,
	CHANNEL2 = 2,
	CHANNEL3 = 3,
	CHANNEL4 = 4,
	CHANNEL5 = 5,
	CHANNEL6 = 6,
	CHANNEL7 = 7,
}DMA_Channel_t;

typedef struct{
	uint16_t numOfTransations;
	DMA_Direction_t direction;
	DMA_FunctionalState_t circularMode;
	DMA_FunctionalState_t peripheralIncrementMode;
	DMA_FunctionalState_t memoryIncrementMode;
	DMA_Size_t PSIZE;
	DMA_Size_t MSIZE;
	DMA_Priority_t priority;
	DMA_Channel_t channel;
}DMA_Config_t;

typedef struct{
	DMA_Stream_TypeDef* instance;
	DMA_Config_t config;
}DMA_HandlerTypeDef;


#define DMA1_Stream0				(DMA_Stream_TypeDef*)0x40026010
#define DMA1_Stream1				(DMA_Stream_TypeDef*)0x40026028
#define DMA1_Stream2				(DMA_Stream_TypeDef*)0x40026040
#define DMA1_Stream3				(DMA_Stream_TypeDef*)0x40026058
#define DMA1_Stream4				(DMA_Stream_TypeDef*)0x40026070
#define DMA1_Stream5				(DMA_Stream_TypeDef*)0x40026088
#define DMA1_Stream6				(DMA_Stream_TypeDef*)0x400260A0
#define DMA1_Stream7				(DMA_Stream_TypeDef*)0x400260B8














#endif /* INC_HAL_DMA_H_ */





