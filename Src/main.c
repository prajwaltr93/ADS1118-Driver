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

#define buff_size 6
uint8_t message[buff_size] = {'h', 'e', 'l', 'l', 'o', '\n'};

int main(void)
{
	if(!(UARTInit(USART2) == UARTSuccess)) {
		// TODO: indicate using an LED that Initialization has Failed
		return 0;
	}

    /* Loop forever */
	UARTWriteBuff(USART2, message, buff_size);
	// TODO: implement delay function
	while(1) {
	}

	return 0;
}