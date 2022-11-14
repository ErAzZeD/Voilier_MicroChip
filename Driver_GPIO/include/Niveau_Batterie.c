#include "Niveau_Batterie.h"

#include "Driver_Timer.h"
#include "Driver_GPIO.h"
#include "Driver_ADC.h"

#define CHANNEL 5

void Handler_Batt(void)
{
}

void Battery_level(void){
	MyGPIO_Init(GPIOA,5,In_Analog);
	MyADC_Init(CHANNEL,Handler_Batt);
	MyADCStartConv(CHANNEL);

}
