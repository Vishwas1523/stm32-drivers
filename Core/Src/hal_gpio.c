
#include "hal_gpio.h"


//function to configure the mode of gpio pin
void GPIO_config(GPIO_TypeDef* GPIO, uint32_t Mode, uint8_t pin_number){
	GPIO->MODER &= ~(3U << (2 * pin_number));
	GPIO->MODER |= (Mode << (2 * pin_number));
	}

//*********************************************************************************
//function to configure the input mode
void GPIO_Input_Config(GPIO_TypeDef* GPIO, uint32_t PullUp_PullDown, uint8_t pin_number){
	switch(PullUp_PullDown){
		case NO_PULLUP_PULLDOWN:
			GPIO->PUPDR &= ~(3<<(2*pin_number));
			break;
		case PULLUP:
			GPIO->PUPDR |= (1<<(2*pin_number));
			break;
		case PULLDOWN:
			GPIO->PUPDR |= (2<<(2*pin_number));
			break;
}
}

//**********************************************************************
//function to configure AF mode
void GPIO_AF_Config(GPIO_TypeDef* GPIO, uint8_t pin_number, uint8_t alternate_function, uint32_t Output_Type, uint32_t Output_Speed, uint32_t PullUp_PullDown){
	if(pin_number < 8)
	{
	    GPIO->AFR[0] &= ~(0xFU << (4*pin_number));
	    GPIO->AFR[0] |=  (alternate_function << (4*pin_number));
	}
	else
	{
	    GPIO->AFR[1] &= ~(0xFU << (4*(pin_number-8)));
	    GPIO->AFR[1] |=  (alternate_function << (4*(pin_number-8)));
	}

		GPIO->OTYPER &= ~(1U << pin_number);
		GPIO->OTYPER |= (Output_Type << pin_number);

		GPIO->OSPEEDR &= ~(3U << (2 * pin_number));
		GPIO->OSPEEDR |= (Output_Speed << (2 * pin_number));


		GPIO->PUPDR &= ~(3U << (2 * pin_number));
		GPIO->PUPDR |= (PullUp_PullDown << (2 * pin_number));
}


//********************************************************************************
//function to configure the output mode of the gpio pin
void GPIO_Output_Config(GPIO_TypeDef* GPIO, uint32_t Output_Type, uint32_t Output_Speed, uint32_t PullUp_PullDown, uint8_t pin_number){
	GPIO->OTYPER &= ~(1U << pin_number);
	GPIO->OTYPER |= (Output_Type << pin_number);

	GPIO->OSPEEDR &= ~(3U << (2 * pin_number));
	GPIO->OSPEEDR |= (Output_Speed << (2 * pin_number));


	GPIO->PUPDR &= ~(3U << (2 * pin_number));
	GPIO->PUPDR |= (PullUp_PullDown << (2 * pin_number));
}

//*************************************************************************************************
//function to read the input data
uint8_t GPIO_Read(GPIO_TypeDef* GPIO, uint8_t pin_number){
	if(GPIO->IDR & (1U << pin_number)){
		return HIGH;
	}
	else return LOW;
}

//************************************************************************************************
//function to write the output data
void GPIO_Write(GPIO_TypeDef* GPIO, uint8_t pin_number, uint8_t output_value){
	if(output_value == HIGH){
		GPIO->BSRR = (1U<<pin_number);
	} else {
		GPIO->BSRR = (1U<<(pin_number + 16));
	}
}

//**************************************************************************************************
//function to toggle the output data
void GPIO_Toggle_Pin(GPIO_TypeDef* GPIO, uint8_t pin_number){
	GPIO->ODR ^= (1U<<pin_number);
}

//******************************************************************************************************
//function to initialize the GPIO
void GPIO_Init(GPIO_Type MyGPIO){
	if(MyGPIO.GPIO == GPIOA) GPIOA_CLOCK_ENABLE_;
	if(MyGPIO.GPIO == GPIOB) GPIOB_CLOCK_ENABLE_;
	if(MyGPIO.GPIO == GPIOC) GPIOC_CLOCK_ENABLE_;
	if(MyGPIO.GPIO == GPIOD) GPIOD_CLOCK_ENABLE_;

	GPIO_config(MyGPIO.GPIO, MyGPIO.Mode, MyGPIO.pin_number);
	if(MyGPIO.Mode == OUTPUT_MODE) GPIO_Output_Config(MyGPIO.GPIO, MyGPIO.Output_Type, MyGPIO.Output_Speed, MyGPIO.PullUp_PullDown, MyGPIO.pin_number);
	else if(MyGPIO.Mode == AF_MODE) GPIO_AF_Config(MyGPIO.GPIO, MyGPIO.pin_number, MyGPIO.alternate_function, MyGPIO.Output_Type, MyGPIO.Output_Speed, MyGPIO.PullUp_PullDown);
	else GPIO_Input_Config(MyGPIO.GPIO, MyGPIO.PullUp_PullDown, MyGPIO.pin_number);
}

//***************************************************************************************************************************
//function to configure GPIO interrupts
void GPIO_Interrupt_Config(GPIO_TypeDef* GPIO, uint8_t pin_number, edge_t edge){
	RCC->APB2ENR |= (1U<<14);  //enabling clock for system configuration so that interrupts can work

	//enabling external interrupts for the ports in sysconfig registers
	if(GPIO == GPIOA){
		if(pin_number <= 3) SYSCFG->EXTICR[0] &= ~(15U<<(4*pin_number));
		if(pin_number <= 7 && pin_number > 3) SYSCFG->EXTICR[1] &= ~(15U<<(4*(pin_number%4)));
		if(pin_number <= 11 && pin_number > 7) SYSCFG->EXTICR[2] &= ~(15U<<(4*(pin_number%8)));
		if(pin_number <= 15 && pin_number > 11) SYSCFG->EXTICR[3] &= ~(15U<<(4*(pin_number%12)));
	}

	if(GPIO == GPIOB){
		if(pin_number <= 3) SYSCFG->EXTICR[0] |= (1U<<(4*pin_number));
		if(pin_number <= 7 && pin_number > 3) SYSCFG->EXTICR[1] |= (1U<<(4*(pin_number%4)));
		if(pin_number <= 11 && pin_number > 7) SYSCFG->EXTICR[2] |= (1U<<(4*(pin_number%8)));
		if(pin_number <= 15 && pin_number > 11) SYSCFG->EXTICR[3] |= (1U<<(4*(pin_number%12)));
	}

	if(GPIO == GPIOC){
		if(pin_number <= 3) SYSCFG->EXTICR[0] |= (2U<<(4*pin_number));
		if(pin_number <= 7 && pin_number > 3) SYSCFG->EXTICR[1] |= (2U<<(4*(pin_number%4)));
		if(pin_number <= 11 && pin_number > 7) SYSCFG->EXTICR[2] |= (2U<<(4*(pin_number%8)));
		if(pin_number <= 15 && pin_number > 11) SYSCFG->EXTICR[3] |= (2U<<(4*(pin_number%12)));
	}

	if(GPIO == GPIOD){
		if(pin_number <= 3) SYSCFG->EXTICR[0] |= (3U<<(4*pin_number));
		if(pin_number <= 7 && pin_number > 3) SYSCFG->EXTICR[1] |= (3U<<(4*(pin_number%4)));
		if(pin_number <= 11 && pin_number > 7) SYSCFG->EXTICR[2] |= (3U<<(4*(pin_number%8)));
		if(pin_number <= 15 && pin_number > 11) SYSCFG->EXTICR[3] |= (3U<<(4*(pin_number%12)));
	}

	//deciding the edge for the interrupts
	switch(edge){
	case RISING_EDGE:
		EXTI->RTSR |= (1U<<pin_number);
		break;

	case FALLING_EDGE:
		EXTI->FTSR |= (1U<<pin_number);
		break;

	case RISING_AND_FALLING_EDGE:
		EXTI->FTSR |= (1U<<pin_number);
		EXTI->RTSR |= (1U<<pin_number);
		break;
	}
}


//***************************************************************************************************************************
//function to enable the interrupts which we configured earlier
void GPIO_Interrupt_Enable(uint8_t pin_number, IRQn_Type IRQ_Number){
	EXTI->IMR |= (1U<<pin_number);	//enabling the pin number in external interrupts
	__NVIC_EnableIRQ(IRQ_Number);  //enabling the interrupt request in nvic for the particular irq number
}

//***************************************************************************************************************************
//function the clear the pending bit
void GPIO_Interrupt_Clear(uint8_t pin_number){
	EXTI->PR |= (1U<<pin_number);
}











