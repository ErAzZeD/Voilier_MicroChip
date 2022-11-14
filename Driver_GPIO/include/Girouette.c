#include "Girouette.h"
#include "Driver_Timer.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"

int isInit = 0;

void initGirouette() {
	//Init timer incrémental
	MyTimer_Base_Init(TIM2, 720, 0);
	MyTimer_INC(TIM2);
	MyTimer_Base_Start(TIM2);	
	
	//PWM pour contrôler le servomoteur
	MyTimer_Base_Init(TIM3, 0xEA5F, 0x17); //periode de 20ms
	MyTimer_PWM(TIM3, 3); //PB0
	MyGPIO_Init(GPIOB, 0, AltOut_Ppull);
	MyTimer_Base_Start(TIM3);
	
	//Zero Girouette
	MyGPIO_Init(GPIOC, 12, In_PullDown);
	while(!isInit){
		if(MyGPIO_Read(GPIOC, 12) == 1){
			isInit = 1;	
			TIM2->CNT = 0;
		}
	}
}

float getAngle() {
	return (TIM2->CNT)/2;
}


float calculDuty(float angle){
	float d;
	int angleScaled = (int) angle;
	
	if(angleScaled <= 45 || angleScaled > 315){
		d=10;
	} else{
		
		if(angleScaled > 180) {
			angleScaled = 180-(angleScaled-180);
		}
		
		d =  angleScaled*(-0.037) + 11.665 ;
	}
	return d;
}
