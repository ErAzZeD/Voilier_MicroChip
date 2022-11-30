#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"

#include "Driver_UART.h"
#include "Girouette.h"

#include "orientation_Plateau.h"
#include "Niveau_Batterie.h"

#include <stdio.h>

float duty;
float angle;

int a;

void writeBattery(void) {
	char snum[3];
	int i;
	Battery_level();
	a = (int) (get_conv()*0.0244)+1;
	sprintf(snum, "%d", a);
	for (i = 0; i < 3; i++) {
		MyUART_SendData(snum[i]);
	}
	MyUART_SendData('%');
	MyUART_SendData('\n');
	TIM1->SR &= ~(0x1 <<0);
}

signed int toto ;
int main ( void )
{
	int i;	
	char auriol[30] = "Auriol le meilleur <3<3<3<3<3\n";

	MyGPIO_Init(GPIOA,5,In_Analog);
	MyGPIO_Init(GPIOA,1, In_Floating);
	MyGPIO_Init(GPIOA,0, In_Floating);

	MyUART_Init();
	MyTimer_Base_Init(TIM4,0xEA5F,0x017);
	MyTimer_Base_Start(TIM4);
	Orientation_Plateau_Init();	
	

	init_ADC();
	
	MyTimer_Base_Init(TIM1, 0xEA55, 0x1770);
	//MyTimer_Base_Init(TIM1,0xEA5F,0x017);
	MyTimer_ActiveIT(TIM1, 1, *writeBattery);
	MyTimer_Base_Start(TIM1);
	
	initGirouette();
	
	for (i = 0; i < 30; i++) {
			MyUART_SendData(auriol[i]);
	}
	
		
	while(1) {
		angle = getAngle();
		duty = calculDuty(angle);
		MyTimer_SetDutyCicle(TIM3, 3, duty);
	}
}

void USART3_IRQHandler(void) {
	while (!(USART3->SR & (1<<5))); 
	toto = USART3->DR;  // Read the data. 
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



