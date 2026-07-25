/*
 * output_compare.h
 *
 *  Created on: Jun 10, 2026
 *      Author: VICTUS
 */

#ifndef INC_OUTPUT_COMPARE_H_
#define INC_OUTPUT_COMPARE_H_
#include "stm32f446xx.h"
#include <stdint.h>

typedef enum{
	OC_CHANNEL_1 = 0,
	OC_CHANNEL_2,
	OC_CHANNEL_3,
	OC_CHANNEL_4
}OC_Channel_t;


typedef enum{
	OC_HIGH = 0,
	OC_LOW
}OC_Polarity_t;


typedef enum{
	FROZEN = 0,
	ACTIVE_LEVEL,
	INACTIVE_LEVEL,
	TOGGLE,
	FORCE_INACTIVE,
	FORCE_ACTIVE,
	OC_PWM_MODE_1,
	OC_PWM_MODE_2
}OC_Mode_t;


typedef enum{
	OC_UPCOUNTING = 0,
	OC_DOWNCOUNTING
}OC_Direction_t;


typedef enum{
	OC_PRELOAD_DISABLE = 0,
	OC_PRELOAD_ENABLE
}OC_Preload_Status_t;

typedef struct{
	TIM_TypeDef* TIMx;
	uint32_t prescaler;
	uint32_t auto_reload;
	OC_Channel_t channel;
	OC_Polarity_t polarity;
	OC_Mode_t mode;
	OC_Direction_t direction;
	uint32_t compare_val;
	OC_Preload_Status_t preload;
}OC_Config_t;

void OC_Init(OC_Config_t* MyOC);
void OC_Start(OC_Config_t* MyOC);
void OC_Stop(OC_Config_t* MyOC);
void OC_SetCompare(OC_Config_t* MyOC, uint32_t compVal);
uint32_t OC_GetCompare(OC_Config_t* MyOC);
void OC_EnableIT(OC_Config_t* MyOC);
void OC_DisableIT(OC_Config_t* MyOC);
#endif /* INC_OUTPUT_COMPARE_H_ */


