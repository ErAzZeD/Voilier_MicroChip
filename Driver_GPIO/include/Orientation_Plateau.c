#include "orientation_plateau.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

void Orientation_Plateau(){
	int i;
	MyTimer_PWM(TIM4,2);
	// Sort sur un pin par defaut
	MyTimer_SetDutyCicle(TIM4,2,44);
	//rotation
	//MyGPIO_Set(GPIOB,2);
	MyGPIO_Init(GPIOB, 7, AltOut_Ppull);
	MyGPIO_Init(GPIOB, 2, Out_Ppull);
	MyGPIO_Set(GPIOB,2);
	for(i = 0; i < 100000000; i++);
	MyGPIO_Reset(GPIOB,2);

	

	
}