/*
 * SPI.h
 *
 *  Created on: Mar 27, 2024
 *      Author: Prajwal T R
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f3xx.h"
#define AHB_GPIOA_EN 			(1U << 17)

void SPIInit(void);

#endif /* SPI_H_ */
