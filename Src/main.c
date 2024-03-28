/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "UART.h"
#include "SPI.h"
#include "GeneralPurposeTimer.h"

#define buff_size 2
uint8_t message[buff_size];

int main(void)
{
	int i = 0;
	int max_temp = 70;
	if(!(UARTInit(USART2) == UARTSuccess)) {
		// TODO: indicate using an LED that Initialization has Failed
		return 0;
	}

	if(!((delayInit(TIM2)) == TimerSuccess)) {
		// TODO: indicate using an LED that Initialization has Failed
		return 0;
	}

	SPIInit();

	// TODO: implement delay function
	while(1) {
		/*
		for(; i < max_temp; i++) {
			message[0] = '0' + (i / 10);
			message[1] = (char)('0' + (i % 10));
			UARTWriteBuff(USART2, message, 2U);

			// wait here
			delayMS(TIM2, 10000);
		}
		i = 0;
		*/
		SPIWrite();
		delayMS(TIM2, 10000);
	}

	return 0;
}
