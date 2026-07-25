/*
 * pwm.h
 *
 *  Created on: Jun 5, 2026
 *      Author: VICTUS
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_
#include "stm32f446xx.h"
#include <stdint.h>

typedef enum{
	PWM_MODE_1 = 0,
	PWM_MODE_2
}PWM_Mode_t;

typedef enum{
	PWM_HIGH = 0,
	PWM_LOW
}PWM_Polarity_t;

typedef enum{
	PWM_UPCOUNTING = 0,
	PWM_DOWNCOUNTING,
	PWM_CENTER_ALIGN_1,
	PWM_CENTER_ALIGN_2
}PWM_Direction_t;

typedef enum{
	PWM_CHANNEL_1 = 0,
	PWM_CHANNEL_2,
	PWM_CHANNEL_3,
	PWM_CHANNEL_4
}PWM_Channel_t;

typedef struct{
	TIM_TypeDef* TIMx;
	PWM_Channel_t channel;
	uint32_t prescaler;
	uint32_t auto_reload;
	uint32_t compare_val;
	PWM_Mode_t mode;
	PWM_Polarity_t polarity;
	PWM_Direction_t direction;
}PWM_Config_t;

void PWM_Init(PWM_Config_t* MyPWM);
void PWM_Start(PWM_Config_t* MyPWM);
void PWM_Stop(PWM_Config_t* MyPWM);
void PWM_SetCompare(PWM_Config_t* MyPWM, uint32_t compVal);
void PWM_SetDuty(PWM_Config_t* MyPWM, uint32_t dutyPercentage);
#endif /* INC_PWM_H_ */
