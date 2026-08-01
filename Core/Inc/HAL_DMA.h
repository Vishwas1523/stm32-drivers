
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
	DMA_DIRECTION_PER_TO_MEM = 0,
	DMA_DIRECTION_MEM_TO_PER = 1,
	DMA_DIRECTION_MEM_TO_MEM = 2
}DMA_Direction_t;

typedef enum{
	DMA_DATA_SIZE_BYTE = 0,
	DMA_DATA_SIZE_HALF_WORD = 1,
	DMA_DATA_SIZE_WORD = 2
}DMA_Size_t;

typedef enum{
	DMA_PRIORITY_LOW = 0,
	DMA_PRIORITY_MEDIUM = 1,
	DMA_PRIORITY_HIGH = 2,
	DMA_PRIORITY_VERY_HIGH = 3
}DMA_Priority_t;

typedef enum{
	DMA_CHANNEL0 = 0,
	DMA_CHANNEL1 = 1,
	DMA_CHANNEL2 = 2,
	DMA_CHANNEL3 = 3,
	DMA_CHANNEL4 = 4,
	DMA_CHANNEL5 = 5,
	DMA_CHANNEL6 = 6,
	DMA_CHANNEL7 = 7,
}DMA_Channel_t;

typedef struct{
	DMA_Direction_t direction;
	DMA_FunctionalState_t circularMode;
	DMA_FunctionalState_t peripheralIncrementMode;
	DMA_FunctionalState_t memoryIncrementMode;
	DMA_Size_t PSIZE;
	DMA_Size_t MSIZE;
	DMA_Priority_t priority;
	DMA_Channel_t channel;
}DMA_Stream_Config_t;

typedef struct{
	DMA_Stream_TypeDef* instance;
	DMA_Stream_Config_t config;
}DMA_HandlerTypeDef;

//------------------------DMA1 Streams and their addresses---------------------
#define DMA1_Stream0				(DMA_Stream_TypeDef*)0x40026010
#define DMA1_Stream1				(DMA_Stream_TypeDef*)0x40026028
#define DMA1_Stream2				(DMA_Stream_TypeDef*)0x40026040
#define DMA1_Stream3				(DMA_Stream_TypeDef*)0x40026058
#define DMA1_Stream4				(DMA_Stream_TypeDef*)0x40026070
#define DMA1_Stream5				(DMA_Stream_TypeDef*)0x40026088
#define DMA1_Stream6				(DMA_Stream_TypeDef*)0x400260A0
#define DMA1_Stream7				(DMA_Stream_TypeDef*)0x400260B8

//------------------------DMA2 Streams and their addresses---------------------
#define DMA2_Stream0				(DMA_Stream_TypeDef*)0x40026410
#define DMA2_Stream1				(DMA_Stream_TypeDef*)0x40026428
#define DMA2_Stream2				(DMA_Stream_TypeDef*)0x40026440
#define DMA2_Stream3				(DMA_Stream_TypeDef*)0x40026458
#define DMA2_Stream4				(DMA_Stream_TypeDef*)0x40026470
#define DMA2_Stream5				(DMA_Stream_TypeDef*)0x40026488
#define DMA2_Stream6				(DMA_Stream_TypeDef*)0x400264A0
#define DMA2_Stream7				(DMA_Stream_TypeDef*)0x400264B8

//------------------------DMA BIT MANIPULATION & MASKING----------------------
#define DMA_CR_EN					(1<<0)
#define DMA_CR_CHSEL_Pos			 25UL
#define DMA_CR_PL_Pos				 16UL
#define DMA_CR_DIR_Pos				 6UL
#define DMA_CR_PINC_Pos				 9UL
#define DMA_CR_MINC_Pos				 10UL
#define DMA_CR_CIRC_Pos				 8UL
#define DMA_CR_PSIZE_Pos			 11UL
#define DMA_CR_MSIZE_Pos			 13UL






void DMA_Init(DMA_HandlerTypeDef* hdma);
void DMA_Start(DMA_HandlerTypeDef* hdma, uint32_t srcAddress, uint32_t dstAddress, uint16_t numOfTransfers);







#endif /* INC_HAL_DMA_H_ */





