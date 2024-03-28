/*
 * SPI.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Prajwal T R
 */

#include "SPI.h"

// SPI Init
void SPIInit(void) {
	// Enable GPIOA if not already and set pin's to alternate function
	if(!(RCC->AHBENR & AHB_GPIOA_EN)) {
		RCC->AHBENR |= AHB_GPIOA_EN;
	}

	// PIN 4, 5, 6, 7 to AF
	// PIN 4
	GPIOA->MODER |= (1U << 9);
	GPIOA->MODER &= ~(1U << 8);

	// PIN 5
	GPIOA->MODER |= (1U << 11);
	GPIOA->MODER &= ~(1U << 10);

	// PIN 6
	GPIOA->MODER |= (1U << 13);
	GPIOA->MODER &= ~(1U << 12);

	// PIN 7
	GPIOA->MODER |= (1U << 15);
	GPIOA->MODER &= ~(1U << 14);

	// set to AF5, 0101
	// PIN 4
	GPIOA->AFR[0] |= (1U << 16);
	GPIOA->AFR[0] &= ~(1U << 17);
	GPIOA->AFR[0] |= (1U << 18);
	GPIOA->AFR[0] &= ~(1U << 19);

	// PIN 5
	GPIOA->AFR[0] |= (1U << 20);
	GPIOA->AFR[0] &= ~(1U << 21);
	GPIOA->AFR[0] |= (1U << 22);
	GPIOA->AFR[0] &= ~(1U << 23);

	// PIN 4
	GPIOA->AFR[0] |= (1U << 24);
	GPIOA->AFR[0] &= ~(1U << 25);
	GPIOA->AFR[0] |= (1U << 26);
	GPIOA->AFR[0] &= ~(1U << 27);

	// PIN 4
	GPIOA->AFR[0] |= (1U << 28);
	GPIOA->AFR[0] &= ~(1U << 29);
	GPIOA->AFR[0] |= (1U << 30);
	GPIOA->AFR[0] &= ~(1U << 31);

	// Enable SPI1
	RCC->APB2ENR |= (1U << 12);

	// ADS1118 needs CPOL = 1, CPHA = 1
	SPI1->CR1 |= (1U << 0);
	SPI1->CR1 &= ~(1U << 1);

	// MC is master
	SPI1->CR1 |= (1U << 2);

	// enable software slave management, SSI bit setting will result in
	// slave selection
	SPI1->CR1 |= (1U << 9);

	// full duplex on separate lines
	SPI1->CR1 &= ~(1U << 15);

	// MSB First
	SPI1->CR1 &= ~(1U << 7);

	// configure data size 16bit for now
	SPI1->CR2 |= (1U << 0);
	SPI1->CR2 |= (1U << 1);
	SPI1->CR2 |= (1U << 2);
	SPI1->CR2 &= ~(1U << 3);

	//Enable SPI1
	SPI1->CR1 |= (1U << 6);

	return;
}
// SPI write
void SPIWrite(void) {

	// also select slave
	SPI1->CR1 &= ~(1U << 8);

	uint8_t size = 2U;
	uint8_t data = 'c';
	while(size--) {
		// wait for TxE
		while(!(SPI1->SR & (1U << 1)));
		SPI1->DR = data;
		size--;
	}
	while(!(SPI1->SR & (1U << 1)));

	while((SPI1->SR & (1U << 7)));

	SPI1->CR1 |= (1U << 8);

	return;
}

// SPI Read
void SPIRead(void) {
	uint8_t size = 2U;
	uint8_t data;
	while(size--) {
		// wait for RXNE
		while(!(SPI1->SR & (1U << 0)));
		data = SPI1->DR;
		size--;
	}
	return;
}


