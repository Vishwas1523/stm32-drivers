/*
 * timers.c
 *
 *  Created on: May 27, 2026
 *      Author: VICTUS
 */

#include "timers.h"
//******************************* Input Capture Functions *****************************************

//function to configure and initialize the input caputre mode along with the channel
void IC_Init(IC_Config_t* MyTim){
	if(MyTim->channel == IC_CHANNEL_1){
		switch (MyTim->selection){
		case Direct:
			MyTim->TIMx->CCMR1 &= ~(3<<0);
			MyTim->TIMx->CCMR1 |= (1<<0);
			break;

		case Indirect:
			MyTim->TIMx->CCMR1 &= ~(3<<0);
			MyTim->TIMx->CCMR1 |= (2<<0);
			break;
		}

		MyTim->TIMx->CCMR1 &= ~(15<<4);
		MyTim->TIMx->CCMR1 |= (MyTim->filter<<4);
		MyTim->TIMx->CCER |= (1<<0);
		MyTim->TIMx->CCER &= ~(1<<1);
		MyTim->TIMx->CCER |= (MyTim->polarity<<1);
		MyTim->TIMx->CCMR1 &= ~(3<<2);
	}

	else if(MyTim->channel == IC_CHANNEL_2){
		switch (MyTim->selection){
		case Direct:
			MyTim->TIMx->CCMR1 &= ~(3<<8);
			MyTim->TIMx->CCMR1 |= (1<<8);
			break;

		case Indirect:
			MyTim->TIMx->CCMR1 &= ~(3<<8);
			MyTim->TIMx->CCMR1 |= (2<<8);
			break;
			}

		MyTim->TIMx->CCMR1 &= ~(15<<12);
		MyTim->TIMx->CCMR1 |= (MyTim->filter<<12);
		MyTim->TIMx->CCER |= (1<<4);
		MyTim->TIMx->CCER &= ~(1<<5);
		MyTim->TIMx->CCER |= (MyTim->polarity<<5);
		MyTim->TIMx->CCMR1 &= ~(3<<10);
	}

	else if(MyTim->channel == IC_CHANNEL_3){
		switch (MyTim->selection){
		case Direct:
			MyTim->TIMx->CCMR2 &= ~(3<<0);
			MyTim->TIMx->CCMR2 |= (1<<0);
			break;

		case Indirect:
			MyTim->TIMx->CCMR2 &= ~(3<<0);
			MyTim->TIMx->CCMR2 |= (2<<0);
			break;
			}

		MyTim->TIMx->CCMR2 &= ~(15<<4);
		MyTim->TIMx->CCMR2 |= (MyTim->filter<<4);
		MyTim->TIMx->CCER |= (1<<8);
		MyTim->TIMx->CCER &= ~(1<<9);
		MyTim->TIMx->CCER |= (MyTim->polarity<<9);
		MyTim->TIMx->CCMR2 &= ~(3<<2);
	}

	else if (MyTim->channel == IC_CHANNEL_4){
		switch (MyTim->selection){
		case Direct:
			MyTim->TIMx->CCMR2 &= ~(3<<8);
			MyTim->TIMx->CCMR2 |= (1<<8);
			break;

		case Indirect:
			MyTim->TIMx->CCMR2 &= ~(3<<8);
			MyTim->TIMx->CCMR2 |= (2<<8);
			break;
			}

		if(MyTim->filter > 15) return;


		MyTim->TIMx->CCMR2 &= ~(15<<12);
		MyTim->TIMx->CCMR2 |= (MyTim->filter<<12);
		MyTim->TIMx->CCER |= (1<<12);
		MyTim->TIMx->CCER &= ~(1<<13);
		MyTim->TIMx->CCER |= (MyTim->polarity<<13);
		MyTim->TIMx->CCMR2 &= ~(3<<10);
	}

	MyTim->TIMx->PSC = MyTim->prescaler;
	MyTim->TIMx->ARR = MyTim->auto_reload;
	MyTim->TIMx->EGR |= TIM_EGR_UG;

	if(MyTim->direction == UPCOUNTING) MyTim->TIMx->CR1 &= ~(1<<4);
	else MyTim->TIMx->CR1 |= (1<<4);


	MyTim->TIMx->CR1 &= ~(3<<5);
}

//after configurating our input capture mode now we can decide when to start it with this function
void IC_Start(IC_Config_t *MyTim){
    MyTim->TIMx->CR1 |= TIM_CR1_CEN;
}

//this function stops the input capture mode
void IC_Stop(IC_Config_t *MyTim){
    MyTim->TIMx->CR1 &= ~TIM_CR1_CEN;
}

//this function is used to get the value stored in registers when the input is captured
uint32_t IC_GetCaptureValue(IC_Config_t *MyTim){
	switch (MyTim->channel){
	case IC_CHANNEL_1:
		return MyTim->TIMx->CCR1;

	case IC_CHANNEL_2:
		return MyTim->TIMx->CCR2;

	case IC_CHANNEL_3:
		return MyTim->TIMx->CCR3;

	case IC_CHANNEL_4:
		return MyTim->TIMx->CCR4;

	default:
		return 0;
	}
}

//this function is to clear the the CCxIF flag in status register, if flags are not cleared then
//we cannot start another interrupt capture with that channel

void IC_ClearFlag(IC_Config_t *MyTim){
    switch(MyTim->channel)
    {
        case IC_CHANNEL_1:
            MyTim->TIMx->SR &= ~TIM_SR_CC1IF;
            break;

        case IC_CHANNEL_2:
            MyTim->TIMx->SR &= ~TIM_SR_CC2IF;
            break;

        case IC_CHANNEL_3:
            MyTim->TIMx->SR &= ~TIM_SR_CC3IF;
            break;

        case IC_CHANNEL_4:
            MyTim->TIMx->SR &= ~TIM_SR_CC4IF;
            break;
    }
}

//this function enables the interrupt in that particular channel
void IC_EnableInterrupt(IC_Config_t *MyTim){
    switch(MyTim->channel){
        case IC_CHANNEL_1:
            MyTim->TIMx->DIER |= TIM_DIER_CC1IE;
            break;

        case IC_CHANNEL_2:
            MyTim->TIMx->DIER |= TIM_DIER_CC2IE;
            break;

        case IC_CHANNEL_3:
        	MyTim->TIMx->DIER |= TIM_DIER_CC3IE;
        	break;

        case IC_CHANNEL_4:
            MyTim->TIMx->DIER |= TIM_DIER_CC4IE;
            break;
    }
}

//this function disables the interrupts
void IC_DisableInterrupt(IC_Config_t *MyTim){
    switch(MyTim->channel){
        case IC_CHANNEL_1:
            MyTim->TIMx->DIER &= ~TIM_DIER_CC1IE;
            break;

        case IC_CHANNEL_2:
            MyTim->TIMx->DIER &= ~TIM_DIER_CC2IE;
            break;

        case IC_CHANNEL_3:
        	MyTim->TIMx->DIER &= ~TIM_DIER_CC3IE;
        	break;

        case IC_CHANNEL_4:
            MyTim->TIMx->DIER &= ~TIM_DIER_CC4IE;
            break;
    }
}

