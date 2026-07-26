
#ifndef INC_UART_H_
#define INC_UART_H_
#include "stm32f446xx.h"
#include <stdint.h>
#include <string.h>
#define UART_Default_Value			0U


typedef enum{
	UART_8_BIT_DATA = 0,
	UART_9_BIT_DATA
}UART_WordLength_t;

typedef enum{
	UART_1_STOP_BIT = 0,
	UART_2_STOP_BIT = 2
}UART_StopBits_t;

typedef enum{
	UART_DISABLE = 0,
	UART_ENABLE
}UART_FunctionalState_t;

typedef enum{
    UART_BAUD_9600   = 9600,
    UART_BAUD_115200 = 115200
}UART_BaudRate_t;

typedef struct{
	UART_WordLength_t wordLength;
	UART_StopBits_t stopBits;
	UART_FunctionalState_t dmaTxEnable;
	UART_FunctionalState_t intTxEnable;
	UART_FunctionalState_t dmaRxEnable;
	UART_FunctionalState_t intRxEnable;
	UART_FunctionalState_t recieveEnable;
	UART_FunctionalState_t transmitEnable;
	UART_BaudRate_t baudRate;
}UART_Config_t;


typedef struct{
	USART_TypeDef* instance;
	UART_Config_t config;
}UART_HandlerTypeDef_t;


void UART_Set_BaudRate(UART_HandlerTypeDef_t* huart);
void UART_Init(UART_HandlerTypeDef_t* huart);
void UART_Transmit(UART_HandlerTypeDef_t* huart, char data);
uint8_t UART_Receive(UART_HandlerTypeDef_t* huart);
void UART_Transmit_IT(UART_HandlerTypeDef_t* huart, char data);
uint8_t UART_Receive_IT(UART_HandlerTypeDef_t* huart);
void UART_Transmit_String(UART_HandlerTypeDef_t* huart, char* str);
#endif /* INC_UART_H_ */
