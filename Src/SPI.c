/*
 * SPI.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Prajwal T R
 */

#include "SPI.h"

#define default_config_register_value 0x59BU
// SPI Init
void SPIInit(void) {
	// Enable GPIOA if not already and set pin's to alternate function
	if(!(RCC->AHBENR & AHB_GPIOA_EN)) {
		RCC->AHBENR |= AHB_GPIOA_EN;
	}

	// PIN 4, 5, 6, 7 to AF
	// PIN 4
	/*
	GPIOA->MODER |= (1U << 9);
	GPIOA->MODER &= ~(1U << 8);
	*/

//	/*
	GPIOA->ODR |= (1U << 4);
	GPIOA->MODER |= (1U << 8);
	GPIOA->MODER &= ~(1U << 9);
//	*/

	// PIN 5
	GPIOA->MODER |= (1U << 11);
	GPIOA->MODER &= ~(1U << 10);

	/*
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
	*/

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
//	SPI1->CR1 &= ~(1U << 9);
	SPI1->CR1 &= ~(1U << 8);

	// full duplex on separate lines
	/*
	 * 2-line unidirectional data mode selected
	 */
	SPI1->CR1 &= ~(1U << 15);

	// MSB First
	SPI1->CR1 &= ~(1U << 7);

	// generate RXNE if 16 bits of data has arrived
	SPI1->CR2 &= ~(1U << 12);

	// configure data size 16bit for now
	SPI1->CR2 |= (1U << 8);
	SPI1->CR2 |= (1U << 9);
	SPI1->CR2 |= (1U << 10);
	SPI1->CR2 |= (1U << 11);
//	SPI1->CR2 &= ~(1U << 11);

	// SS is enabled if SPI is enabled in master mode
	SPI1->CR2 |= (1U << 2);

	//Enable SPI1
	SPI1->CR1 |= (1U << 6);

	return;
}
// SPI write
void SPIWrite(void) {
	// also select slave
	GPIOA->ODR &= ~(1U << 4);

	uint8_t size = 1U;
	uint8_t data = 'D';
	uint8_t data_1 = 'c';
	while(size--) {
		// wait for TxE
		while(!(SPI1->SR & (1U << 1)));
//		SPI1->DR = (uint16_t)((uint16_t)(data << 8) | data_1);
		SPI1->DR = default_config_register_value;
	}

	while(!(SPI1->SR & (1U << 1)));
	while((SPI1->SR & (1U << 7)));

	while((SPI1->SR & 0x1800U)); // FIFO empty [12:11] 00

	GPIOA->ODR |= (1U << 4);
	return;
}

// SPI Read
void SPIRead(void) {
	// wait for RXNE
	GPIOA->ODR &= ~(1U << 4);

	while(!(SPI1->SR & (1U << 0)));
	uint8_t size = 1U;
	uint16_t data;

	while(size--) {
		data = SPI1->DR;
	}
	GPIOA->ODR |= (1U << 4);
	return;
}


