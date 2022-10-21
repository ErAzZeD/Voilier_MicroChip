#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"



void MyADC_Init(int channel, void (*IT_function)(void)); // A MODIFIER PAR LES ATTRIBUTS DE LA STRUCTURE TIMER 
void MyADCStartConv(int channel) ;

#endif
