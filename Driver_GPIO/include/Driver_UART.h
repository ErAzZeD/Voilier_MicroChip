#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"


void MyUART_Init();
void MyUART_SendData (char c);
signed int MyUART_GetData (void);


#endif
