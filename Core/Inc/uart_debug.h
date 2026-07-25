#ifndef INC_UART_DEBUG_H_
#define INC_UART_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "stm32f446xx.h"

#define DEBUG_UART USART2

void uart_init(void);
void UART_printf(char *msg, ...);

#endif /* INC_UART_DEBUG_H_ */

