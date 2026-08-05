#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f446xx.h"
#include <stdint.h>

typedef enum{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
	ADC_CHANNEL_14,
	ADC_CHANNEL_15,
	ADC_CHANNEL_16,
	ADC_CHANNEL_17,
	ADC_CHANNEL_18
}ADC_channel_t;


typedef enum{
	ADC_RESOLUTION_12_BITS = 0,
	ADC_RESOLUTION_10_BITS,
	ADC_RESOLUTION_8_BITS,
	ADC_RESOLUTION_6_BITS
}ADC_resolution_t;



typedef enum{
	ADC_RIGHT_ALIGNMENT = 0,
	ADC_LEFT_ALIGNMENT
}ADC_dataAlignment_t;


typedef enum{
	ADC_SAMPLING_CYCLES_3 = 0,
	ADC_SAMPLING_CYCLES_15,
	ADC_SAMPLING_CYCLES_28,
	ADC_SAMPLING_CYCLES_56,
	ADC_SAMPLING_CYCLES_84,
	ADC_SAMPLING_CYCLES_112,
	ADC_SAMPLING_CYCLES_144,
	ADC_SAMPLING_CYCLES_480
}ADC_samplingTime_t;


typedef enum{
	ADC_PCLK_DIV_2 = 0,
	ADC_PCLK_DIV_4,
	ADC_PCLK_DIV_6,
	ADC_PCLK_DIV_8
}ADC_prescaler_t;


typedef enum{
	ADC_DISABLE = 0,
	ADC_ENABLE
}ADC_state_t;


typedef enum{
	ADC_TRIGGER_SOFTWARE = 0,
	ADC_TIM1_CC1_TRIG,
	ADC_TIM1_CC2,
	ADC_TIM1_CC3,
	ADC_TIM2_CC2,
	ADC_TIM2_CC3,
	ADC_TIM2_CC4,
	ADC_TIM2_TRGO,
	ADC_TIM3_CC1,
	ADC_TIM3_TRGO,
	ADC_TIM4_CC4,
	ADC_TIM5_CC1,
	ADC_TIM5_CC2,
	ADC_TIM5_CC3,
	ADC_TIM8_CC1,
	ADC_TIM8_TRGO,
	ADC_EXTI_LINE_11
}ADC_configTrigger_t;


typedef enum{
	ADC_EDGE_DISABLE = 0,
	ADC_RISING_EDGE,
	ADC_FALLING_EDGE,
	ADC_RISING_AND_FALLING_EDGE
}ADC_timerEdge_t;

typedef enum{
    ADC_EOC_SEQUENCE = 0,
    ADC_EOC_EACH_CONVERSION
}ADC_EOCSelection_t;

typedef struct{
	ADC_channel_t channel;
	ADC_samplingTime_t samplingTime;
}ADC_channelConfig_t;

typedef struct{
	ADC_resolution_t resolution;
	ADC_channelConfig_t channels[16];
	ADC_dataAlignment_t alignment;
	ADC_state_t scanMode;
	ADC_state_t continuousMode;
	ADC_state_t dmaMode;
	ADC_configTrigger_t trigger;
	ADC_timerEdge_t edge;
	uint8_t numConversions;
	ADC_EOCSelection_t eocSelection;
}ADC_config_t;


typedef struct{
	ADC_TypeDef* instance;
	ADC_config_t config;
}ADC_HandleTypeDef;

void ADC_ConfigPrescaler(ADC_prescaler_t prescaler);
void ADC_Start(ADC_HandleTypeDef* hadc);
void ADC_Stop(ADC_HandleTypeDef* hadc);
void ADC_Init(ADC_HandleTypeDef* hadc);
uint16_t ADC_GetValue(ADC_HandleTypeDef* hadc);
#endif /* INC_ADC_H_ */
