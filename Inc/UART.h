/*
 * UART.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Prajwal T R
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f3xx.h"

#define AHB_GPIOA_EN 			(1U << 17)
#define USART2_TX_EMPTY 			(1U << 7)
#define UART2_CR1_EN				(1U << 0)
#define UART2_CR1_TXE				(1U << 3)
#define UART2_CR1_TXIE				(1U << 7)
#define UART2_CR1_RXIE				(1U << 5)
#define UART2_CR1_OVR8				(1U << 15)
#define UART2_CR1_TC				(1U << 6)
#define UART2_CR1_RXNE				(1U << 6)
#define UART2_ICR_TCCF				(1U << 6)

enum _UARTInitStatus {
	UARTSuccess = 0,
	UARTFailed
};

typedef enum _UARTInitStatus UARTInitStatus;
typedef enum _UARTInitStatus UARTBRRSetStatus;
typedef enum _UARTInitStatus UARTReadStatus;
typedef enum _UARTInitStatus UARTWriteStatus;

UARTInitStatus UARTInit(USART_TypeDef *UARTReg);
UARTBRRSetStatus UARTSetBRR(USART_TypeDef *USARTx, uint32_t buadRate);
UARTReadStatus UARTReadBuff(USART_TypeDef *USARTx, uint8_t *buff, uint32_t len);
UARTWriteStatus UARTWriteBuff(USART_TypeDef *USARTx, uint8_t *buff, uint32_t len);

#endif /* UART_H_ */
