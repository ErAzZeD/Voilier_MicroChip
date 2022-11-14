#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
/*
*****************************************************************************************
*@brief
*@param−>Paramètre sous forme d’une structure (son adresse) contenant les
informations de base
*@Note−>Fonction à lancer systématiquement avant d’aller plus en détail dans les
conf plus fines (PWM,codeur inc...)
*************************************************************************************************
*/


void MyTimer_Base_Init(TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC); // A MODIFIER PAR LES ATTRIBUTS DE LA STRUCTURE TIMER 

//void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ) ;

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio , void (* IT_function ) ( void ) ); 

void MyTimer_PWM(TIM_TypeDef * Timer , char Channel);

void MyTimer_SetDutyCicle(TIM_TypeDef * Timer , char Channel, float dutyCycle);

void MyTimer_INC(TIM_TypeDef * Timer);

#define MyTimer_Base_Start(Timer) Timer->CR1 = 0x1 // To be continued... :) 
#define MyTimer_Base_Stop(Timer) Timer->CR1 = 0x0


#endif
