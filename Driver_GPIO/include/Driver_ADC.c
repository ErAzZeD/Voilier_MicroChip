#include "Driver_ADC.h"
#include "stm32f10x.h"


void (*fn) (void);

void MyADC_Init(int channel, void (*IT_function)(void)) {
	RCC->APB2ENR |= 0x01 << 9; //MISE EN PLACE HORLOGE
	RCC->CFGR &= ~(3<<14);
	RCC->CFGR |= (2<<14);
	if (channel <= 17) {
		ADC1->CR2 |= 0x1 << 0; //ADON
		ADC1->CR2 |= 0x7 << 17; //EXTSEL		ADC1->CR2 |= 0x1 << 22;
		ADC1->CR2 |= 0x1 << 20;
		ADC1->CR1 |= 0x1 << 5; //EOCIE (génération d'une IT) 
		ADC1->SQR1 |= channel << 0; 
		fn = IT_function;

	}
}

void MyADCStartConv(int channel){
	ADC1->CR2 |= 0x1 << 22; //SWSTART
}


void ADC1_2_IRQHandler(void) {
	if (fn != 0) {
		(*fn)();
	}
}



