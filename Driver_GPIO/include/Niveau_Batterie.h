#ifndef Niveau_Batterie_H
#define Niveau_Batterie_H

#include "stm32f10x.h"
void init_ADC(void);
void Battery_level(void);
int get_conv(void);
#endif 
