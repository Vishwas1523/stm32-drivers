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

    GPIO_Type MyGPIO2;

    MyGPIO2.GPIO = GPIOA;
    MyGPIO2.Mode = AF_MODE;
    MyGPIO2.Output_Speed = FAST_SPEED;
    MyGPIO2.Output_Type = PUSH_PULL;
    MyGPIO2.PullUp_PullDown = NO_PULLUP_PULLDOWN;
    MyGPIO2.pin_number = 3;
    MyGPIO2.alternate_function  = 7;

    GPIO_Init(MyGPIO2);

    UART_HandlerTypeDef_t huart1 = {0};

    huart1.instance = USART2;
    huart1.config.baudRate = UART_BAUD_9600;
    huart1.config.wordLength = UART_8_BIT_DATA;
    huart1.config.stopBits = UART_1_STOP_BIT;
    huart1.config.transmitEnable = UART_ENABLE;
    huart1.config.recieveEnable = UART_ENABLE;
    UART_Init(&huart1);

    UART_Transmit(&huart1, 't');
    uint8_t temp = UART_Receive(&huart1);
    UART_Transmit(&huart1, (char)temp);
    UART_Transmit(&huart1, '\r');
    UART_Transmit(&huart1, '\n');
    while (1){

    }
}
