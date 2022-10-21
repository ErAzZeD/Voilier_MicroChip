#include "Driver_GPIO.h"
#include "stm32f10x.h"

// INPUT PULLUP/PULLDOWN N'EST PAS IMPLEMENTE (PULLDOWN PAR DEFAULT)
void MyGPIO_Init(GPIO_TypeDef * GPIO, int GPIO_Pin, int GPIO_Conf) {
	
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	
	if ((GPIO_Pin >= 0) && (GPIO_Pin <= 7)) {
		GPIO->CRL &= ~(0xF) << (4*GPIO_Pin);
		GPIO->CRL |= GPIO_Conf << (4*GPIO_Pin);	
	}
	
	if (GPIO_Pin > 7 && GPIO_Pin <= 15) {
		GPIO->CRH &= ~(0xF) << (4*(GPIO_Pin-8));
		GPIO->CRH |= GPIO_Conf << (4*(GPIO_Pin-8));	
	}
}

int MyGPIO_Read(GPIO_TypeDef * GPIO,int GPIO_Pin) {
	return (GPIO->IDR & (0x1 << GPIO_Pin)) >> GPIO_Pin;
}

void MyGPIO_Set(GPIO_TypeDef * GPIO,int GPIO_Pin) {
	GPIO->ODR |= (0x1 << GPIO_Pin);
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO,int GPIO_Pin) {
	GPIO->ODR &= ~(0x1 << GPIO_Pin);
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO,int GPIO_Pin) {
	if (MyGPIO_Read(GPIO, GPIO_Pin) == 0){
		MyGPIO_Set(GPIO, GPIO_Pin);
	} else {
		MyGPIO_Reset(GPIO, GPIO_Pin);
	}
}
