#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"


#define In_Floating 0x4 //a completer
#define In_PullDown 0x8 //a completer
#define In_PullUp 0x8 //a completer
#define In_Analog 0x0 //a completer
#define Out_Ppull 0x2 //a completer
#define Out_OD 0x6 //a completer
#define AltOut_Ppull 0xA //a completer
#define AltOut_OD 0xD //a completer

void MyGPIO_Init(GPIO_TypeDef * GPIO, int GPIO_Pin, int GPIO_Conf);
int MyGPIO_Read(GPIO_TypeDef * GPIO,int GPIO_Pin); //renvoie 0 ou autre chose different de 0
void MyGPIO_Set(GPIO_TypeDef * GPIO,int GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef * GPIO,int GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef * GPIO,int GPIO_Pin);
#endif
