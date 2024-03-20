# ADS118 16 bit ADC Driver for STM32F303K8T6

[ADC Information](https://www.ti.com/product/ADS1118)

using [STM32F303K8T6](https://www.st.com/en/microcontrollers-microprocessors/stm32f303k8.html)'s SPI interface, repository contains
drivers written from scratch that reads 16bit sensor values from ADS1118's on board temperature sensor and same is relayed back to
a QT application over UART [Temperature-Reader-Qt](https://github.com/prajwaltr93/Temperature-Reader-Qt).

Few other notable goals:
1. Documenting process of fine tuning ADC parameters 
2. Writing Generic HAL for ADS1118 for STM32 Based Cortex M4 cores.


