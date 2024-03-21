/*
 * GeneralPurposeTimer.c
 *
 *  Created on: Mar 21, 2024
 *      Author: Prajwal T R
 */

#include "GeneralPurposeTimer.h"

TimerStatus delayInit(TIM_TypeDef *TIM) {
	// check if timer is GPtimer 2
	if(TIM != TIM2){
		return TimerFailed;
	}

	// select internal clock
	// set
	TIM->SMCR &= ~TIM2_SMCR_SMS;

	// select counter mode i.e. Down-Counter 0
	TIM->CR1 |= TIM2_CR_DIR;

	// setup One-pulse mode
	TIM->CR1 &= ~TIM2_CR_OPM;

	// adjust pre-scaler

	return TimerSuccess;
}

void delayMS(uint32_t milliseconds) {
}
