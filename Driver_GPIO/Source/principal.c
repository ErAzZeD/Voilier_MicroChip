#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"

int toto ;
void toggleLED(void) {
	//MyGPIO_Toggle(GPIOC, 10);
	//TIM4->SR &= 0x0 <<0;
	MyADCStartConv(0);
	while ((ADC1->SR & (1<<1)) != (1<<1)) {}
	toto =ADC1->DR ;
	ADC1->SR &= ~(1<<1);
	MyADCStartConv(0);
}

void getValueOfADC(void) {
	int valueOfADC = ADC1->DR;
	ADC1->CR2 |= 0x1 << 22;

}

int main ( void )
{
	
	/* --------------- GPIO ----------------------- */
	/*// LED
	MyGPIO_Init(GPIOC, 10, Out_Ppull);
	
	//BOUTON
	MyGPIO_Init(GPIOC, 8, In_PullDown);
	
	do
	{
		if (MyGPIO_Read(GPIOC, 8) == 1) {
			MyGPIO_Set(GPIOC, 10);
		} else {
			MyGPIO_Reset(GPIOC, 10);
		}
	} while ( 1 ) ;*/
	
	
	/* ------------------ TIMERS ------------------ */
	
	/*RCC->APB1ENR |= 0x1;
	TIM2->ARR = 0x257; // Valeur marche interruption
	TIM2->PSC = 0x1770; // Diviseur de 72MHz
	TIM2->CR1 |= 0x1; //Valeur CEN ENABLED (launch clock)*/
	
	
	
	//MyGPIO_Init(GPIOC, 10, Out_Ppull);
	MyTimer_Base_Init(TIM4, 0x257, 0xEA60);
  
	/*MyTimer_PWM(TIM4, 4);
	MyTimer_SetDutyCicle(TIM4, 4, 50);*/
	MyADC_Init(0, (*getValueOfADC));
	
	// 	POUR LA PROCHAINE FOIS : METTRE EN PLACE L'INTERRUPTION A LA PLACE DU WHILE
	MyTimer_ActiveIT (TIM4, 1, (*toggleLED));
	do
	{
		
	} while ( 1 ) ;
}

