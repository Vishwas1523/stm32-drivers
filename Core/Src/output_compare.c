/*
 * output_compare.c
 *
 *  Created on: Jun 10, 2026
 *      Author: VICTUS
 */
#include "output_compare.h"

void OC_Init(OC_Config_t* MyOC){

	MyOC->TIMx->CNT = 0;
	MyOC->TIMx->PSC = MyOC->prescaler;
	MyOC->TIMx->ARR = MyOC->auto_reload;

	volatile uint32_t *CCMR;
	uint32_t oc_mode;
	uint32_t oc_preload;
	uint32_t oc_polarity;
	uint32_t oc_enable = (1<<(MyOC->channel*4));

	switch(MyOC->channel){
	case OC_CHANNEL_1:
		CCMR = &MyOC->TIMx->CCMR1;
		MyOC->TIMx->CCR1 = MyOC->compare_val;
		oc_mode = (MyOC->mode<<4);
		oc_preload = (MyOC->preload<<3);
		oc_polarity = (MyOC->polarity<<1);
		break;

	case OC_CHANNEL_2:
		CCMR = &MyOC->TIMx->CCMR1;
		MyOC->TIMx->CCR2 = MyOC->compare_val;
		oc_mode = (MyOC->mode<<12);
		oc_preload = (MyOC->preload<<11);
		oc_polarity = (MyOC->polarity<<5);
		break;

	case OC_CHANNEL_3:
		CCMR = &MyOC->TIMx->CCMR2;
		MyOC->TIMx->CCR3 = MyOC->compare_val;
		oc_mode = (MyOC->mode<<4);
		oc_preload = (MyOC->preload<<3);
		oc_polarity = (MyOC->polarity<<9);
		break;

	case OC_CHANNEL_4:
		CCMR = &MyOC->TIMx->CCMR2;
		MyOC->TIMx->CCR4 = MyOC->compare_val;
		oc_mode = (MyOC->mode<<12);
		oc_preload = (MyOC->preload<<11);
		oc_polarity = (MyOC->polarity<<13);
		break;

	default:
		return;
	}

	*CCMR &= ~(0xFFFFFFFF<<0);
	*CCMR |= oc_mode | oc_preload;
	MyOC->TIMx->CCER &= ~(0xFFFFFFFF<<0);
	MyOC->TIMx->CCER |= oc_polarity | oc_enable;


}


void OC_Start(OC_Config_t* MyOC){

	MyOC->TIMx->CR1 |= TIM_CR1_CEN;

}


void OC_Stop(OC_Config_t* MyOC){

	MyOC->TIMx->CR1 &= ~TIM_CR1_CEN;

}


void OC_SetCompare(OC_Config_t* MyOC, uint32_t compVal){

	MyOC->compare_val = compVal;
	switch (MyOC->channel){
	case OC_CHANNEL_1:
		MyOC->TIMx->CCR1 = MyOC->compare_val;
		break;
	case OC_CHANNEL_2:
		MyOC->TIMx->CCR2 = MyOC->compare_val;
		break;
	case OC_CHANNEL_3:
		MyOC->TIMx->CCR3 = MyOC->compare_val;
		break;
	case OC_CHANNEL_4:
		MyOC->TIMx->CCR4 = MyOC->compare_val;
		break;
	default:
		return;
	}
}


uint32_t OC_GetCompare(OC_Config_t* MyOC){

	switch (MyOC->channel){
	case OC_CHANNEL_1:
		return MyOC->TIMx->CCR1;
	case OC_CHANNEL_2:
		return MyOC->TIMx->CCR2;
	case OC_CHANNEL_3:
		return MyOC->TIMx->CCR3;
	case OC_CHANNEL_4:
		return MyOC->TIMx->CCR4;
	default:
		return 0;
	}
}


void OC_EnableIT(OC_Config_t* MyOC){

	uint32_t enableINT = (1<<(MyOC->channel + 1));

	MyOC->TIMx->DIER &= ~(0xFFFFFFFF);

	MyOC->TIMx->DIER |= enableINT;

	NVIC_EnableIRQ(28);
}


void OC_DisableIT(OC_Config_t* MyOC){

	uint32_t disableINT = (1<<(MyOC->channel + 1));

	MyOC->TIMx->DIER &= ~disableINT;

}









