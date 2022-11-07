#include "orientation_plateau.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

void Orientation_Plateau_Init() {
	MyTimer_PWM(TIM4,2);
	MyTimer_SetDutyCicle(TIM4,2,0);
	MyGPIO_Init(GPIOB, 7, AltOut_Ppull);
	MyGPIO_Init(GPIOB, 2, Out_Ppull);
	
}

void Orientation_Plateau(int sens, float puissance){
	int power = ((puissance/100)*56)+44;
	MyTimer_SetDutyCicle(TIM4,2,power);
	if (sens == 1) {
		MyGPIO_Set(GPIOB,2);
	} else {
		MyGPIO_Reset(GPIOB,2);
	}

}

void Orientation_Plateau_Stop() {
	MyTimer_SetDutyCicle(TIM4,2,0);

}