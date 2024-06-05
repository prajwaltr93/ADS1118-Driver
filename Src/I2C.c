/*
 * I2C.c
 *
 *  Created on: Apr 18, 2024
 *      Author: Prajwal T R
 */
#include "I2C.h"

#define SlaveADDR			0b1001000 // 72, 0x48

#define SCLLTim				0x9U
#define SCLHTim				0x3U
#define I2CADD10			(1U << 11)
#define I2CRead1			(1U << 10)
#define I2CWrite0			~(1U << 10)


void I2CInit(void) {
	// SDA and SCL PB7 and PB6
	// D4 and D5
	/*
	// Enable Port B
	RCC->AHBENR |= (1U << 18);

	// Configure to Alternate Mode
	GPIOB->MODER |= (1U << 15);
	GPIOB->MODER &= ~(1U << 14);

	// Configure to Alternate Mode
	GPIOB->MODER |= (1U << 13);
	GPIOB->MODER &= ~(1U << 12);

	// select open drain
	GPIOB->OTYPER |= (1U << 6);
	GPIOB->OTYPER |= (1U << 7);

	// high speed
	GPIOB->OSPEEDR |= (1U << 12);
	GPIOB->OSPEEDR |= (1U << 13);

	// high speed
	GPIOB->OSPEEDR |= (1U << 14);
	GPIOB->OSPEEDR |= (1U << 15);

	// pull up, pin 6
	GPIOB->PUPDR |= (1U << 12);
	GPIOB->PUPDR &= ~(1U << 13);

	// pull up, pin 7
	GPIOB->PUPDR |= (1U << 14);
	GPIOB->PUPDR &= ~(1U << 15);

	// set alternate function
	GPIOB->AFR[0] &= ~(1U << 24);
	GPIOB->AFR[0] &= ~(1U << 25);
	GPIOB->AFR[0] |= 	(1U << 26);
	GPIOB->AFR[0] &= ~(1U << 27);

	GPIOB->AFR[0] &= ~(1U << 28);
	GPIOB->AFR[0] &= ~(1U << 29);
	GPIOB->AFR[0] |= 	(1U << 30);
	GPIOB->AFR[0] &= ~(1U << 31);
	*/

	// Enable Port A, PA6 -> A5, PA5 -> A4 (SCL, SDA)
	RCC->AHBENR |= (1U << 17);

	// input floating ?
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER &= ~(1U << 13);

	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER &= ~(1U << 11);

//	// select open drain
//	GPIOA->OTYPER |= (1U << 6);
//	GPIOA->OTYPER |= (1U << 5);
//
//	// high speed
//	GPIOA->OSPEEDR |= (1U << 12);
//	GPIOA->OSPEEDR |= (1U << 13);
//
//	// high speed
//	GPIOA->OSPEEDR |= (1U << 10);
//	GPIOA->OSPEEDR |= (1U << 11);

//	// pull up, pin 6
//	GPIOA->PUPDR |= (1U << 12);
//	GPIOA->PUPDR &= ~(1U << 13);
//
//	// pull up, pin 5
//	GPIOA->PUPDR |= (1U << 10);
//	GPIOA->PUPDR &= ~(1U << 11);

	// Enable I2C
	RCC->APB1ENR |= (1U << 21);

	// modify for fast mode, i.e. timings
	I2C1->TIMINGR |= (0xffU & SCLLTim);
	I2C1->TIMINGR |= (0xff00U & (SCLHTim << 8));

	// SDADEL
	I2C1->TIMINGR |= (0x1 << 16);

	// SCLDEL
	I2C1->TIMINGR |= (0x3 << 20);

	// addressing mode, 7bit
	I2C1->CR2 &= ~I2CADD10;

	// enable automatic end mode, after nbytes are transferred.
//	I2C1->CR2 |= (1U << 25);

	// slave addr, 7 bits, starting from bit 1
	I2C1->CR2 |= (0xfeU & (SlaveADDR << 1));

	// Enable slave control byte ? TODO: not sure what this does
//	I2C1->CR1 |= (1U << 16);

	// Number of bytes, 1 for now
	I2C1->CR2 |= (1U << 16);

	// direction
	I2C1->CR2 &= I2CWrite0;

	I2C1->OAR1 = 0x8401;

	// enable I2C1
	I2C1->CR1 |= (1U << 0);

	return;
}

void I2CWrite(void) {

	// write stop
	I2C1->CR2 |= (1U << 14);

	// Start transfer, generate start
	I2C1->CR2 |= (1U << 13);

	// wait for TXIS, is set when TXDR is empty
	while(!(I2C1->ISR & (1U << 0)));

	// send the byte, 121, 0x79
	I2C1->TXDR = 'y';

	// wait for transfer to complete of nbytes
	while(!(I2C1->ISR & (1U << 6)));

	return;
}

