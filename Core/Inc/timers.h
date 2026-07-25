/*
 * timers.h
 *
 *  Created on: May 27, 2026
 *      Author: VICTUS
 */

#ifndef INC_TIMERS_H_
#define INC_TIMERS_H_
#include "stm32f446xx.h"
#include "hal_gpio.h"
#include <stdint.h>

typedef enum{
	UPCOUNTING = 0,
	DOWNCOUNTING
}IC_Counter_Direction_t;

typedef enum{
	IC_CHANNEL_1 = 0,
	IC_CHANNEL_2,
	IC_CHANNEL_3,
	IC_CHANNEL_4
}ic_channel_t;

typedef enum{
	IC_RISING_EDGE = 0,
	IC_FALLING_EDGE = 1,
	BOTH = 3
}ic_polarity_t;

typedef enum{
	Direct = 0,
	Indirect
}ic_selection_t;

typedef struct{
	TIM_TypeDef* TIMx;
	ic_channel_t channel;
	uint16_t prescaler;
	uint16_t auto_reload;
	ic_polarity_t polarity;
	ic_selection_t selection;
	uint8_t filter;
	IC_Counter_Direction_t direction;
}IC_Config_t;

void IC_Init(IC_Config_t* MyTim);
void IC_Start(IC_Config_t* MyTim);
void IC_Stop(IC_Config_t *MyTim);
uint32_t IC_GetCaptureValue(IC_Config_t *MyTim);
void IC_ClearFlag(IC_Config_t *MyTim);
void IC_EnableInterrupt(IC_Config_t *MyTim);
void IC_DisableInterrupt(IC_Config_t *MyTim);
#endif /* INC_TIMERS_H_ */

