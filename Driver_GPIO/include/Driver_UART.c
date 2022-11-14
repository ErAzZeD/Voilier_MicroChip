#include "Driver_UART.h"
#include "Driver_GPIO.h"
#include "orientation_plateau.h"

void MyUART_Init() {
	
	RCC->APB1ENR |= 1 << 18; //MISE EN PLACE HORLOGE

	/*GPIOA->CRL |= (3<<8);   // output mode 50 MHz for PA2
	GPIOA->CRL |= (2<<10);  // Alternate Func Push Pull For PA2
		
	GPIOA->CRL &= ~(3<<12);   // Input Mode For PA3
	GPIOA->CRL |= (2<<14);  // Input Pull Up/ Down For PA3	*/
	MyGPIO_Init(GPIOB, 11, In_PullDown);
	
	NVIC->ISER[1] |= 0x1 << 7;
	NVIC->IP[25] |= 1 << 4;
	
	
		
	
	
	USART3->CR1 = 0x00;   // Clear ALL
	USART3->CR1 |= (1<<13);   // UE = 1... Enable USART
	USART3->CR1 |= (1<<5);

	USART3->BRR = 0x0EB0;   // BaudRate à CONFIGURER 
		
	USART3->CR1 |= (1<<2); // RE=1.. Enable the Receiver
	USART3->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
	MyGPIO_Init(GPIOB, 10, AltOut_Ppull);

	
}

void MyUART_SendData (char c) {
	
	USART3->DR = c;   // LOad the Data
	while (!(USART3->SR & (1<<7)));  // Wait for TXE to SET.. This indicates that the data has been transmitted

}


signed int MyUART_GetData (void) {

	signed int Temp;
	
	while (!(USART3->SR & (1<<5)));  // Wait for RXNE to SET.. This indicates that the data has been Received
	Temp = USART3->DR;  // Read the data. 
	return Temp;
}

