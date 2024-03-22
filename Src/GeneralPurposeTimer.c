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

	RCC->APB1ENR |= TIM2_APB1_EN;

	// select internal clock
	TIM->SMCR &= ~TIM2_SMCR_SMS;

	// select counter mode i.e. Up-Counter
	TIM->CR1 &= ~TIM2_CR_DIR;

	return TimerSuccess;
}

TimerStatus delayMS(TIM_TypeDef *TIM, uint32_t milliseconds) {
	// check if timer is GPtimer 2
	if(TIM != TIM2){
		return TimerFailed;
	}

	TIM->ARR = milliseconds - 1;

	// adjust pre-scaler
	TIM->PSC = 800U - 1;

	// start counter
	TIM->CR1 |= TIM2_START_CNT;

	// block wait for ISR UIF bit to be set
	while(!(TIM->SR & TIM2_OVERFLW));

	// clear UIF flag
	TIM->SR &= ~TIM2_OVERFLW;

	// stop counter
	TIM->CR1 &= ~TIM2_START_CNT;

	return TimerSuccess;
}
