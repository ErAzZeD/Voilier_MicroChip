#include "orientation_plateau.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

void Orientation_Plateau(){
	MyTimer_PWM(TIM4,2);
	// Sort sur un pin par defaut
	MyTimer_SetDutyCicle(TIM4,1,50);
	//rotation
	MyGPIO_Set(GPIOB,2);
	
}