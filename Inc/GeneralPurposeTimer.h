/*
 * GeneralPuposeTimer.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Prajwal T R
 */

#ifndef GENERALPURPOSETIMER_H_
#define GENERALPURPOSETIMER_H_

#include "stm32f3xx.h"

#define TIM2_SMCR_SMS			(7U << 0)
#define TIM2_CR_DIR				(1U << 4)
#define TIM2_CR_OPM				(1U << 3)
#define TIM2_APB1_EN			(1U << 0)
#define TIM2_START_CNT			(1U << 0)
#define TIM2_OVERFLW			(1U << 0)

enum _TimerStatus {
	TimerSuccess = 0,
	TimerFailed
};

typedef enum _TimerStatus TimerStatus;

TimerStatus delayInit(TIM_TypeDef *TIM);
TimerStatus delayMS(TIM_TypeDef *TIM, uint32_t milliseconds);

#endif /* GENERALPURPOSETIMER_H_ */
