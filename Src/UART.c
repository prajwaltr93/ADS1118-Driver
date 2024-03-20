/*
 * UART.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Prajwal T R
 */


#include "UART.h"

UARTInitStatus UARTInit(USART_TypeDef *UARTReg) {
	// Only interact with UART2, i.e connected to COM PORT USB
	if(UARTReg != USART2) {
		return UARTFailed;
	}
	// TODO: should work with other UART interfaces

	// configure GPIOA
	RCC->AHBENR |= AHB_GPIOA_EN;
	// set to alternate function mode
	// TODO: make this a one-liner
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &= ~(1U << 4);

	// AF7, 0111
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	// configure UART
	RCC->APB1ENR |= (1U << 17);

	// first disable UART, before enabling
	USART2->CR1 &= ~UART2_CR1_EN;

	// TODO: make this a function
//	USART2->BRR = 0x341U; // 9600
	UARTSetBRR(USART2, 9600U);

	// TX enable
	USART2->CR1 = UART2_CR1_TXE;

	// UART enable
	USART2->CR1 |= UART2_CR1_EN;

	return UARTSuccess;
}

UARTBRRSetStatus UARTSetBRR(USART_TypeDef *USART, uint32_t buadRate) {
	// compute required USARTDIV
	uint16_t USARTDIV = 0;

	// TODO: derive fclk
	if(!(USART->CR1 & UART2_CR1_OVR8)) {
		USARTDIV = (8000000U / buadRate);
	}
	else {
		// TODO: handle if over-sampling by 8 is selected
		return UARTFailed;
	}

	USART->BRR = USARTDIV;
}

UARTReadStatus UARTReadBuff(USART_TypeDef *USART, uint8_t *buff, uint32_t len) {
	// TODO: check if Rx is Enabled ?
	// if in interrupt mode
	if((USART->CR1 & UART2_CR1_RXIE)) {
		// TODO: implement this
		return UARTFailed;
	}
	// else
	else {
		while(len--) {
			while((USART->ISR & UART2_CR1_RXNE)); // wait for some data
			*buff = USART->RDR;
			buff++; // TODO: can be merged with above line ?
		}
	}
	return UARTSuccess;
}

UARTWriteStatus UARTWriteBuff(USART_TypeDef *USART, uint8_t *buff, uint32_t len) {
	// TODO: check if Tx is Enabled ?
	// if in interrupt mode
	if((USART->CR1 & UART2_CR1_TXIE)) {
		// TODO: implement this
		return UARTFailed;
	}
	// else
	else {
		while(len--) {
			// Clear transmit complete flag
			USART->ICR |= UART2_ICR_TCCF;

			USART->TDR = *buff;
			buff++;
			while(!(USART->ISR & UART2_CR1_TC)); // wait for transfer to complete
		}
	}

	return UARTSuccess;
}
