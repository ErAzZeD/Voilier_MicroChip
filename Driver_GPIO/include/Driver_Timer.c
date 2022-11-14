#include "Driver_Timer.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"

void (*PFNc) (void);

void MyTimer_Base_Init(TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC) {
	
	// Démarrage de la clock
	if (Timer == TIM1) {
		RCC->APB2ENR |= 0x1 << 11;
	} 
	if (Timer == TIM2) {
		RCC->APB1ENR |= 0x1 << 0;
	}
	if (Timer == TIM3) {
		RCC->APB1ENR |= 0x1 << 1;
	}
	if (Timer == TIM4) {
		RCC->APB1ENR |= 0x1 << 2;
	}


	
	// Configuration et lancement du timer t
	Timer->ARR = ARR;
	Timer->PSC = PSC;
	MyTimer_Base_Start(Timer);
}
	


void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio, void (*IT_function)(void)){
	Timer->DIER |= 0x1 << 0;
	
	// Configuration NVIC (ISER)
	if (Timer == TIM1) {
		NVIC->ISER[0] |= 0x1 << 25;
		NVIC->IP[25] |= Prio << 4;
	} 
	if (Timer == TIM2) {
		NVIC->ISER[0] |= 0x1 << 28;
		NVIC->IP[28] |= Prio << 4;
	}
	if (Timer == TIM3) {
		NVIC->ISER[0] |= 0x1 << 29;
		NVIC->IP[29] |= Prio << 4;
	}
	if (Timer == TIM4) {
		NVIC->ISER[0] |= 0x1 << 30;
		NVIC->IP[30] |= Prio << 4;
	} 
	
	PFNc = IT_function;
}

void MyTimer_PWM(TIM_TypeDef * Timer , char Channel){
	if (Timer == TIM1) {
		TIM1->BDTR |= 0x1 << 15;
		switch (Channel) {
			case(1):
				Timer->CCER |= 1<<0 ;
				Timer->CCMR1 |= 6<< 4 ;
				MyGPIO_Init(GPIOA, 8, AltOut_OD);
				break;
			case(2):
				Timer->CCER |= 1<<4 ;
				Timer->CCMR1 |= 6<< 12 ;
				MyGPIO_Init(GPIOA, 9, AltOut_OD);
				break;
			case(3):
				Timer->CCER |= 1<<8 ;
				Timer->CCMR2 |= 6<< 4 ;
				MyGPIO_Init(GPIOA, 10, AltOut_OD);
				break;
			case(4):
				Timer->CCER |= 1<<12 ;
				Timer->CCMR2 |= 6<< 12 ;
				MyGPIO_Init(GPIOA, 11, AltOut_OD);
				break;
			default:
				break;
		}
	} 
	if (Timer == TIM2) {	
		switch (Channel) {
				case(1):
					Timer->CCER |= 1<<0 ;
					Timer->CCMR1 |= 6<< 4 ;
					MyGPIO_Init(GPIOA, 0, AltOut_OD);
					break;
				case(2):
					Timer->CCER |= 1<<4 ;
					Timer->CCMR1 |= 6<< 12 ;
					MyGPIO_Init(GPIOA, 1, AltOut_OD);
					break;
				case(3):
					Timer->CCER |= 1<<8 ;
					Timer->CCMR2 |= 6<< 4 ;
					MyGPIO_Init(GPIOA, 2, AltOut_OD);
					break;
				case(4):
					Timer->CCER |= 1<<12 ;
					Timer->CCMR2 |= 6<< 12 ;
					MyGPIO_Init(GPIOA, 3, AltOut_OD);
					break;
				default:
					break;
			}
	}
	if (Timer == TIM3) {
		switch (Channel) {
				case(1):
					Timer->CCER |= 1<<0 ;
					Timer->CCMR1 |= 6<< 4 ;
					MyGPIO_Init(GPIOA, 6, AltOut_OD);
					break;
				case(2):
					Timer->CCER |= 1<<4 ;
					Timer->CCMR1 |= 6<< 12 ;
					MyGPIO_Init(GPIOA, 7, AltOut_OD);
					break;
				case(3):
					Timer->CCER |= 1<<8 ;
					Timer->CCMR2 |= 6<< 4 ;
					MyGPIO_Init(GPIOB, 0, AltOut_OD);
					break;
				case(4):
					Timer->CCER |= 1<<12 ;
					Timer->CCMR2 |= 6<< 12 ;
					MyGPIO_Init(GPIOB, 1, AltOut_OD);
					break;
				default:
					break;
			}
	}
	if (Timer == TIM4) {
		switch (Channel) {
				case(1):
					Timer->CCER |= 1<<0 ;
					Timer->CCMR1 |= 6<< 4 ;

					MyGPIO_Init(GPIOB, 6, AltOut_OD);
					break;
				case(2):
					Timer->CCER |= 1<<4 ;
					Timer->CCMR1 |= 6<< 12 ;

					MyGPIO_Init(GPIOB, 7, AltOut_OD);
					break;
				case(3):
						Timer->CCER |= 1<<8 ;
						Timer->CCMR2 |= 6<< 4 ;

					MyGPIO_Init(GPIOB, 8, AltOut_OD);
					break;
				case(4):
						Timer->CCER |= 1<<12 ;
						Timer->CCMR2 |= 6<< 12 ;
						MyGPIO_Init(GPIOB, 9, AltOut_OD);
					break;
				default:
					break;
			}
	} 
}

void MyTimer_SetDutyCicle(TIM_TypeDef * Timer , char Channel, float dutyCycle) {
	  int varCRR = (int) (Timer->ARR * (dutyCycle/100.0));
		switch (Channel) {
			case(1):
				Timer->CCR1 = varCRR;	
				break;
			case(2):
				Timer->CCR2 = varCRR;	
				break;
			case(3):
				Timer->CCR3 = varCRR;	
				break;
			case(4):
				Timer->CCR4 = varCRR;	
				break;
			default:
				break;
		}
}


void TIM1_UP_IRQHandler(void) {
	if (PFNc != 0) {
		(*PFNc)();
	}
}

void TIM2_IRQHandler(void) {
	if (PFNc != 0) {
		(*PFNc)();
	}
}

void TIM3_IRQHandler(void) {
	if (PFNc != 0) {
		(*PFNc)();
	}
}

void TIM4_IRQHandler(void) {
	if (PFNc != 0) {
		(*PFNc)();
	}

}
