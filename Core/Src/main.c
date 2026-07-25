#include "stm32f446xx.h"
#include "hal_gpio.h"
#include "uart_debug.h"
#include "adc.h"
#include "uart.h"


int main(void){

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIO_Type MyGPIO;

    MyGPIO.GPIO = GPIOA;
    MyGPIO.Mode = AF_MODE;
    MyGPIO.Output_Speed = FAST_SPEED;
    MyGPIO.Output_Type = PUSH_PULL;
    MyGPIO.PullUp_PullDown = NO_PULLUP_PULLDOWN;
    MyGPIO.pin_number = 2;
    MyGPIO.alternate_function  = 7;

    GPIO_Init(MyGPIO);

    UART_HandlerTypeDef_t huart1;

    huart1.instance = USART2;
    huart1.config.baudRate = UART_BAUD_9600;
    huart1.config.wordLength = UART_8_BIT_DATA;
    huart1.config.stopBits = UART_1_STOP_BIT;
    huart1.config.transmitEnable = UART_ENABLE;
    huart1.config.recieveEnable = UART_DISABLE;
    UART_Init(&huart1);

    UART_Transmit(&huart1, '\r');

    UART_Transmit(&huart1, 'R');

    UART_Transmit(&huart1, 'E');

    UART_Transmit(&huart1, 'S');

    UART_Transmit(&huart1, 'E');

    UART_Transmit(&huart1, 'T');

    UART_Transmit(&huart1, '\n');

   // NVIC_SystemReset();

    UART_Transmit(&huart1, '\r');

    UART_Transmit(&huart1, 'R');

    UART_Transmit(&huart1, 'E');

    UART_Transmit(&huart1, 'S');

    UART_Transmit(&huart1, 'T');

    UART_Transmit(&huart1, 'A');

    UART_Transmit(&huart1, 'R');

    UART_Transmit(&huart1, 'T');

    UART_Transmit(&huart1, '\n');

    while (1){

    }
}
