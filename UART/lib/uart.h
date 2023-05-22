/*
 *	Header referring to UART functions
 *
 *	File: uart.h
 *
 *	Author: Eduardo Gomes
 *
 */

#ifndef LIB_UART_H_
#define LIB_UART_H_

//_________________ Library _________________________________________
//___________________________________________________________________

#include "stm32f4xx.h"


//_________________ Functions prototypes ____________________________
//___________________________________________________________________

void 	 init_uart1(void);
void 	 TX_uart1  (uint8_t byte);
uint16_t RX_uart1  ();

#endif /* LIB_UART_H_ */
