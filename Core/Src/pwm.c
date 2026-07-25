/*
 * pwm.c
 *
 *  Created on: Jun 5, 2026
 *      Author: VICTUS
 */
#include "pwm.h"
void PWM_Init(PWM_Config_t* MyPWM){
	switch (MyPWM->channel){
	case PWM_CHANNEL_1:
	if(MyPWM->mode == PWM_MODE_1)	MyPWM->TIMx->CCMR1 |= (6<<4);
	else if (MyPWM->mode == PWM_MODE_2)	MyPWM->TIMx->CCMR1 |= (7<<4);
	MyPWM->TIMx->CCMR1 |= TIM_CCMR1_OC1PE;
	MyPWM->TIMx->CCER |= (MyPWM->polarity<<1);
	MyPWM->TIMx->CCER |= TIM_CCER_CC1E;
	MyPWM->TIMx->CCR1 = MyPWM->compare_val;
	break;

	case PWM_CHANNEL_2:
	if(MyPWM->mode == PWM_MODE_1)	MyPWM->TIMx->CCMR1 |= (6<<12);
	else if (MyPWM->mode == PWM_MODE_2)	MyPWM->TIMx->CCMR1 |= (7<<12);
	MyPWM->TIMx->CCMR1 |= TIM_CCMR1_OC2PE;
	MyPWM->TIMx->CCER |= (MyPWM->polarity<<5);
	MyPWM->TIMx->CCER |= TIM_CCER_CC2E;
	MyPWM->TIMx->CCR2 = MyPWM->compare_val;
	break;

	case PWM_CHANNEL_3:
	if(MyPWM->mode == PWM_MODE_1)	MyPWM->TIMx->CCMR2 |= (6<<4);
	else if (MyPWM->mode == PWM_MODE_2)	MyPWM->TIMx->CCMR2 |= (7<<4);
	MyPWM->TIMx->CCMR2 |= TIM_CCMR2_OC3PE;
	MyPWM->TIMx->CCER |= (MyPWM->polarity<<9);
	MyPWM->TIMx->CCER |= TIM_CCER_CC3E;
	MyPWM->TIMx->CCR3 = MyPWM->compare_val;
	break;

	case PWM_CHANNEL_4:
	if(MyPWM->mode == PWM_MODE_1)	MyPWM->TIMx->CCMR2 |= (6<<12);
	else if (MyPWM->mode == PWM_MODE_2)	MyPWM->TIMx->CCMR2 |= (7<<12);
	MyPWM->TIMx->CCMR2 |= TIM_CCMR2_OC4PE;
	MyPWM->TIMx->CCER |= (MyPWM->polarity<<13);
	MyPWM->TIMx->CCER |= TIM_CCER_CC4E;
	MyPWM->TIMx->CCR4 = MyPWM->compare_val;
	break;
	}

	MyPWM->TIMx->CR1 |= TIM_CR1_ARPE;

	if(MyPWM->direction == PWM_UPCOUNTING) MyPWM->TIMx->CR1 &= ~TIM_CR1_DIR;
	else if(MyPWM->direction == PWM_DOWNCOUNTING) MyPWM->TIMx->CR1 |= TIM_CR1_DIR;
	else if(MyPWM->direction == PWM_CENTER_ALIGN_1){
			MyPWM->TIMx->CR1 &= ~TIM_CR1_DIR;
			MyPWM->TIMx->CR1 |= (2<<5);
		}
	else if(MyPWM->direction == PWM_CENTER_ALIGN_2){
			MyPWM->TIMx->CR1 |= TIM_CR1_DIR;
			MyPWM->TIMx->CR1 |= (2<<5);
		}

	MyPWM->TIMx->ARR = MyPWM->auto_reload;
	MyPWM->TIMx->PSC = MyPWM->prescaler;

	MyPWM->TIMx->EGR |= TIM_EGR_UG;
}


void PWM_Start(PWM_Config_t* MyPWM){
	MyPWM->TIMx->CR1 |= TIM_CR1_CEN;
}


void PWM_Stop(PWM_Config_t* MyPWM){
	MyPWM->TIMx->CR1 &= ~TIM_CR1_CEN;
}


void PWM_SetCompare(PWM_Config_t* MyPWM, uint32_t compVal){
	switch (MyPWM->channel){
	case PWM_CHANNEL_1:
		MyPWM->TIMx->CCR1 = compVal;
		break;

	case PWM_CHANNEL_2:
		MyPWM->TIMx->CCR2 = compVal;
		break;

	case PWM_CHANNEL_3:
		MyPWM->TIMx->CCR3 = compVal;
		break;

	case PWM_CHANNEL_4:
		MyPWM->TIMx->CCR4 = compVal;
		break;

	default:
		return;
	}
}


void PWM_SetDuty(PWM_Config_t* MyPWM, uint32_t dutyPercentage){
	if(dutyPercentage > 100) return;

	switch (MyPWM->channel){
	case PWM_CHANNEL_1:
		MyPWM->compare_val = ((MyPWM->auto_reload + 1)* dutyPercentage)/100;
		MyPWM->TIMx->CCR1 = MyPWM->compare_val;
		break;

	case PWM_CHANNEL_2:
		MyPWM->compare_val = ((MyPWM->auto_reload + 1)* dutyPercentage)/100;
		MyPWM->TIMx->CCR2 = MyPWM->compare_val;
		break;

	case PWM_CHANNEL_3:
		MyPWM->compare_val = ((MyPWM->auto_reload + 1)* dutyPercentage)/100;
		MyPWM->TIMx->CCR3 = MyPWM->compare_val;
		break;

	case PWM_CHANNEL_4:
		MyPWM->compare_val = ((MyPWM->auto_reload + 1)* dutyPercentage)/100;
		MyPWM->TIMx->CCR4 = MyPWM->compare_val;
		break;

	default:
		return;
	}
}






