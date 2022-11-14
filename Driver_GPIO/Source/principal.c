#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Driver_UART.h"

#include "orientation_Plateau.h"
#include "Niveau_Batterie.h"


int toto ;
int titi;




signed int toto ;
int main ( void )
{
	int i;
	MyUART_Init();
	MyTimer_Base_Init(TIM4,0xEA5F,0x017);
	Orientation_Plateau_Init();	
	Battery_level();


	while(1) {
		for (i =0; i<1000000; i++);
		MyUART_SendData('f');
	}

}

void USART3_IRQHandler(void) {
	while (!(USART3->SR & (1<<5))); 
	toto = USART3->DR;  // Read the data. 
	while (1) {
	  toto = MyUART_GetData();	

		if (toto > 0 && toto <= 100) {
			Orientation_Plateau(1, toto);
		}
		if (toto > 0 && toto >= 156) {
			Orientation_Plateau(0, -(toto-255));
		}
		if (toto == 0) {
			Orientation_Plateau_Stop();
		}

		
	}


}

