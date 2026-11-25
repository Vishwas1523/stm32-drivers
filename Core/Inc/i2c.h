#ifndef INC_IIC_H_
#define INC_IIC_H_

#include "stm32f446xx.h"
#include <stdint.h>

/* IIC structure */
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;
}IIC_Typedef;

/* Enable Clocks*/
#define __IIC1_CLOCK_ENABLE()			(RCC->APB1ENR |= (1U<<21U))
#define __IIC2_CLOCK_ENABLE()			(RCC->APB1ENR |= (1U<<22U))
#define __IIC3_CLOCK_ENABLE()			(RCC->APB1ENR |= (1U<<23U))

/* IIC peripheral addresses */
#define IIC_Offset					0x400
#define IIC_1						((IIC_Typedef*)(0x40005400))
#define IIC_2						((IIC_Typedef*)(IIC_1 + IIC_Offset))
#define IIC_3						((IIC_Typedef*)(IIC_2 + IIC_Offset))

/* IIC operations */
#define IIC_START_GEN				(1U<<8U)
#define IIC_STOP_GEN				(1U<<9U)
#define IIC_TxE_SET					(1U<<7U)
#define IIC_BTF_SET					(1U<<2U)

typedef enum{
	IIC_Tx_MODE	= 0,
	IIC_Rx_MODE
}IIC_ControllerMode_t;

typedef enum{
	Sm_MODE_IIC = 0,
	Fm_MODE_IIC
}IIC_ControllerSpeed_t;	/* Set the speed for IIC controller */

typedef enum{
	IIC_PE_DISABLE = 0,
	IIC_PE_ENABLE
}IIC_PE_Config_t;	/* Enable the IIC peripherals */

/* IIC Configuration structure*/
typedef struct{
	uint8_t freq:6;		/* Set the frequency of peripheral clock. Min = 0x2 and Max = 0x45. */
	uint16_t ccr_val:12;	/* Set the CCR value for generating SCL frequency. */
	IIC_ControllerMode_t mode;
	uint8_t riseTime:6;		/* Set the rise time for SCL. */
	IIC_PE_Config_t	peripheralEnable;
	uint8_t address;	/* Address of the target or receiver. Use only 7 bit address for now. */
	IIC_ControllerSpeed_t speed;
}IIC_Config_t;

/* IIC Handler Structure */
typedef struct{
	IIC_Typedef* instance;
	IIC_Config_t* config;
}IIC_HandlerTypeDef;



/* IIC functions */
void IIC_ControllerStart(IIC_HandlerTypeDef* hiic);
void IIC_ControllerStop(IIC_HandlerTypeDef* hiic);
void IIC_ControllerTransmit(IIC_HandlerTypeDef* hiic, uint8_t* data, size_t size);




#endif










