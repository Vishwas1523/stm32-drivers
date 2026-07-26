#include "uart.h"

void UART_Set_BaudRate(UART_HandlerTypeDef_t* huart){
    if(huart->instance == USART1 || huart->instance == USART6)
        huart->instance->BRR = (90000000 + huart->config.baudRate / 2U)/huart->config.baudRate;
    else
        huart->instance->BRR = (16000000 + huart->config.baudRate / 2U)/huart->config.baudRate;
}

void UART_Init(UART_HandlerTypeDef_t* huart){
    huart->instance->CR1 &= ~(USART_CR1_UE);
    huart->instance->CR1 &= ~(USART_CR1_M);
    huart->instance->CR1 |= (huart->config.wordLength << USART_CR1_M_Pos);
    huart->instance->CR2 &= ~(USART_CR2_STOP);
    huart->instance->CR2 |= (huart->config.stopBits << 12);
    huart->instance->CR3 &= ~(USART_CR3_DMAT);
    huart->instance->CR3 |= (huart->config.dmaTxEnable << USART_CR3_DMAT_Pos);
    huart->instance->CR3 &= ~(USART_CR3_DMAR);
    huart->instance->CR3 |= (huart->config.dmaRxEnable << USART_CR3_DMAR_Pos);
    UART_Set_BaudRate(huart);
    huart->instance->CR1 &= ~(USART_CR1_TE);
    huart->instance->CR1 |= (huart->config.transmitEnable << USART_CR1_TE_Pos);
    huart->instance->CR1 &= ~(USART_CR1_RE);
    huart->instance->CR1 |= (huart->config.recieveEnable << USART_CR1_RE_Pos);
    huart->instance->CR1 &= ~(USART_CR1_RXNEIE);
    huart->instance->CR1 |= (huart->config.intRxEnable << USART_CR1_RXNEIE_Pos);
    huart->instance->CR1 &= ~(USART_CR1_TXEIE);
    huart->instance->CR1 |= (huart->config.intTxEnable << USART_CR1_TXEIE_Pos);
    huart->instance->CR1 |= USART_CR1_UE;
}

void UART_Transmit(UART_HandlerTypeDef_t* huart, char data){
    while (!(huart->instance->SR & USART_SR_TXE)){}
    huart->instance->DR = (uint8_t)data;
    while (!(huart->instance->SR & USART_SR_TC)){}
}

uint8_t UART_Receive(UART_HandlerTypeDef_t* huart){
    while(!(huart->instance->SR & USART_SR_RXNE)){}
    return huart->instance->DR;
}

void UART_Transmit_IT(UART_HandlerTypeDef_t* huart, char data){
    huart->instance->DR = (uint8_t)data;
    huart->instance->CR1 |= (huart->config.intTxEnable << USART_CR1_TXEIE_Pos);
}

uint8_t UART_Receive_IT(UART_HandlerTypeDef_t* huart){
    return (uint8_t)(huart->instance->DR & 0xFF);
}
