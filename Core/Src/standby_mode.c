/*
 * standby_mode.c
 *
 *  Created on: May 22, 2026
 *      Author: VICTUS
 */
#include "standby_mode.h"
#include "uart_debug.h"
#include "core_cm4.h"
void standby_Msg(void){
	uart_init();
    if(PWR->CSR & PWR_CSR_SBF){

        UART_printf("\r\nWoke up from Standby\n");

        // Clear Standby flag
        PWR->CR |= PWR_CR_CSBF;

        // Clear Wakeup flag
        PWR->CR |= PWR_CR_CWUF;
    }
    else{
        UART_printf("\r\nPower-on Reset\n");
    }
}

void go_to_sleep(void){

    // 1. Enable PWR clock
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    // 2. Clear Wakeup flag
    PWR->CR |= PWR_CR_CWUF;

    // 3. Select Standby mode
    PWR->CR |= PWR_CR_PDDS;

    // 4. Enable Wakeup Pin 1 (PA0)
    PWR->CSR |= PWR_CSR_EWUP1;

    // 5. Set SLEEPDEEP bit
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // 6. Disable SysTick
    SysTick->CTRL = 0;

    // 7. Enter Standby
    __WFI();
}

