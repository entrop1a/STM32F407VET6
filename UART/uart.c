/*
 *	UART functions
 *
 *	File: uart.c
 *
 *	Author: Eduardo Gomes
 *
 */

//_________________ Library _________________________________________
//___________________________________________________________________

#include "uart.h"


//_________________ Development of functions ________________________
//___________________________________________________________________


void init_uart1(void){

	// Pin configuration

	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;		//Enable clock to USART1
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		//Enable clock to GPIOA

	GPIOA -> MODER |= GPIO_MODER_MODER9_1;  	//Set PA9 as OUTPUT Alternate function
	GPIOA -> MODER &= ~GPIO_MODER_MODER9_0;

	GPIOA -> MODER |= GPIO_MODER_MODER10_1;		//Set PA10 as INPUT
	GPIOA -> MODER &= ~GPIO_MODER_MODER10_0;

	GPIOA -> AFR[1] |=   GPIO_AFRH_AFSEL9_0		//Set function of PA9 to USART1
			|    GPIO_AFRH_AFSEL9_1
			|    GPIO_AFRH_AFSEL9_2;
	GPIOA -> AFR[1] &= ~(GPIO_AFRH_AFSEL9_3);

	GPIOA -> AFR[1] |=   GPIO_AFRH_AFSEL10_0	//Set function of PA10 to USART1
			|    GPIO_AFRH_AFSEL10_1
			|    GPIO_AFRH_AFSEL10_2;
	GPIOA -> AFR[1] &= ~(GPIO_AFRH_AFSEL10_3);


	// Definitions of UART1

	USART1 -> CR1 = 0x00; 	 	 	//Reset state CR1

	USART1 -> CR1 |= USART_CR1_UE	 	// Enable USART
		      |  USART_CR1_TE	 	// Enable TX
		      |  USART_CR1_RE;	 	// Enable RX

	USART1 -> CR1 &= ~(USART_CR1_M);	// Determine => [1 start bit, 8 data bits, n stop bit]


	// Boud rate

	/*
	 * BAUD = f_ck/(16*USARTDIV)
	 * 9600 = 16 MHz/(16*USARTDIV)
	 * USARTDIV = 107,17
	 *
	 * DIV_MANTISSA = 0d107 ; DIV_FRACTION = 0d16 * 0d0,17 = 0d2,72 ~= 0d3
	 * BRR = (DIV_MANTISSA << 4) | (DIV_FRACTION) = 0d1715
	 * BRR = 0x6B3
	 *
	 */

	USART1 -> BRR = 0x6B3; //Define boud rate = 9600

} // End init_uart1()


void TX_uart1(uint8_t byte){

	while(!(USART1 -> SR & USART_SR_TXE)); // Check transmission occurrence
	USART1 -> DR = byte;

} // End TX_uart1()


uint16_t RX_uart1(){

	while(!(USART1 -> SR & USART_SR_RXNE));
	return USART1 -> DR;

} // End RX_uart1()
