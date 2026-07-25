#include "adc.h"

void ADC_Start(ADC_HandleTypeDef* hadc){
	hadc->instance->CR2 |= ADC_CR2_ADON;
	for(volatile int i = 0; i < 100000; i++){}
	hadc->instance->CR2 |= ADC_CR2_ADON;
	if(hadc->config.trigger == ADC_TRIGGER_SOFTWARE)	hadc->instance->CR2 |= ADC_CR2_SWSTART;

}

void ADC_Stop(ADC_HandleTypeDef* hadc){
	hadc->instance->CR2 &=  ~ADC_CR2_ADON;
}

static void ADC_ConfigTrigger(ADC_HandleTypeDef* hadc){
	if(hadc->config.trigger == ADC_TRIGGER_SOFTWARE) return;
	int temp = hadc->config.trigger - 1;
	hadc->instance->CR2 &= ~((0xF << 24) | (0x3 << 28));
	hadc->instance->CR2 |= (temp<<24);
	hadc->instance->CR2 |= (hadc->config.edge<<28);
}


static void ADC_ConfigChannels(ADC_HandleTypeDef* hadc){
	if(hadc->config.numConversions == 0) return;
		hadc->instance->SQR1 &= ~(0xF << 20);
		hadc->instance->SQR1 |= ((hadc->config.numConversions - 1) << 20);
		for(int rank = 0; rank < hadc->config.numConversions; rank++){
		    uint32_t channel =  hadc->config.channels[rank].channel;

		    if(rank < 6){
		        hadc->instance->SQR3 &= ~(0x1F << (rank * 5));
		        hadc->instance->SQR3 |=  (channel << (rank * 5));
		    }
		    else if(rank < 12){
		        hadc->instance->SQR2 &= ~(0x1F << ((rank - 6) * 5));
		        hadc->instance->SQR2 |=  (channel << ((rank - 6) * 5));
		    }
		    else{
		        hadc->instance->SQR1 &= ~(0x1F << ((rank - 12) * 5));
		        hadc->instance->SQR1 |=  (channel << ((rank - 12) * 5));
		    }
		}
		for(int i = 0; i<hadc->config.numConversions; i++){
			for(int i = 0; i < hadc->config.numConversions; i++){
			    uint32_t channel = hadc->config.channels[i].channel;
			    uint32_t sampleTime = hadc->config.channels[i].samplingTime;

			    if(channel < 10){
			        uint32_t shift = channel * 3;

			        hadc->instance->SMPR2 &= ~(0x7U << shift);
			        hadc->instance->SMPR2 |=  (sampleTime << shift);
			    }
			    else{
			        uint32_t shift = (channel - 10) * 3;

			        hadc->instance->SMPR1 &= ~(0x7U << shift);
			        hadc->instance->SMPR1 |=  (sampleTime << shift);
			    }
			}
}

}

void ADC_Init(ADC_HandleTypeDef* hadc){
	hadc->instance->CR1 &= ~((3U<<24) | (1U<<8));
	hadc->instance->CR1 |= (hadc->config.resolution<<24) |	(hadc->config.scanMode<<8);
	hadc->instance->CR2 &= ~((1U<<1) | (1U<<8) | (1U<<10) | (1U<<11));
	hadc->instance->CR2 |= (hadc->config.continuousMode<<1) | (hadc->config.dmaMode<<8) | (hadc->config.alignment<<11);
	if(hadc->config.eocSelection == ADC_EOC_EACH_CONVERSION){
	    hadc->instance->CR2 |= ADC_CR2_EOCS;
	}else	hadc->instance->CR2 &= ~ADC_CR2_EOCS;

	ADC_ConfigTrigger(hadc);
	ADC_ConfigChannels(hadc);
}


void inline ADC_ConfigPrescaler(ADC_prescaler_t prescaler){
	ADC->CCR		&=		~(3U<<16);
	ADC->CCR		|=		(prescaler<<16);
}

uint16_t ADC_GetValue(ADC_HandleTypeDef* hadc){
	return hadc->instance->DR;
}


