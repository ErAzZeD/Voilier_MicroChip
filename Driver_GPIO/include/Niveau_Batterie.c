#include "Niveau_Batterie.h"

#include "Driver_Timer.h"
#include "Driver_GPIO.h"
#include "Driver_ADC.h"

#define CHANNEL 5

static int finale_conv;

void Handler_Batt(void)
{
	finale_conv = ADC1->DR;
}

void init_ADC(void)
{
	MyADC_Init(CHANNEL,Handler_Batt);
}

void Battery_level(void){
	MyADCStartConv(CHANNEL);
}

int get_conv(){
	return finale_conv;
}
