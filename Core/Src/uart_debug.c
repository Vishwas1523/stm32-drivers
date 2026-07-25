
#include "uart_debug.h"

void uart_init(void)
{
    /* Enable clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* PA2 -> USART2_TX */

    /* Set PA2 to Alternate Function mode */
    GPIOA->MODER &= ~(3U << (2 * 2));
    GPIOA->MODER |=  (2U << (2 * 2));

    /* Select AF7 for USART2 */
    GPIOA->AFR[0] &= ~(0xF << (4 * 2));
    GPIOA->AFR[0] |=  (7U  << (4 * 2));

    /* Optional GPIO settings */
    GPIOA->OSPEEDR |= (3U << (2 * 2));

    /* Configure baud rate
       Assuming APB1 clock = 16 MHz
       Baudrate = 9600
    */
    USART2->BRR = 0x0683;

    /* Enable transmitter */
    USART2->CR1 |= USART_CR1_TE;

    /* Enable USART */
    USART2->CR1 |= USART_CR1_UE;
}

void UART_printf(char *msg, ...)
{
    char buff[80];

    va_list args;

    va_start(args, msg);
    vsprintf(buff, msg, args);
    va_end(args);

    for (int i = 0; i < strlen(buff); i++)
    {
        while (!(USART2->SR & USART_SR_TXE));

        USART2->DR = buff[i];
    }

    /* Wait until transmission complete */
    while (!(USART2->SR & USART_SR_TC));
}
