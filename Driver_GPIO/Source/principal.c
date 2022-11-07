#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Driver_UART.h"

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

signed int toto ;
int main ( void )
{
	
	/*uint8_t buffer[30];
	int indx = 0;*/
	
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
	/*MyTimer_Base_Init(TIM4, 0x257, 0xEA60);
  
	/*MyTimer_PWM(TIM4, 4);
	MyTimer_SetDutyCicle(TIM4, 4, 50);*/
	/*MyADC_Init(0, (*getValueOfADC));
	
	// 	POUR LA PROCHAINE FOIS : METTRE EN PLACE L'INTERRUPTION A LA PLACE DU WHILE
	MyTimer_ActiveIT (TIM4, 1, (*toggleLED));*/
	
	MyUART_Init();
	
		
		
	
	
	while (1)
	{
	/*	buffer[indx] = MyUART_GetData();
 		indx++;
 		if (indx>=1) {*/
		//	MyUART_SendData('H');
		/*	indx = 0;
		}*/
		toto = MyUART_GetData();	
		if (toto < 0) {
			// Configurer bit de sens négatif
			// Configurer vitesse de rotation (avec un offset à définir)
		} else {
			// Configurer bit de sens positif
			// Configurer vitesse de rotation (avec un offset à définir)
		}
	}  
	
}

