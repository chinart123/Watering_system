/* Watering_System/Core/Src/HAL/hal_gpio.c */
#include "hal_gpio.h"

/* Declare platform-specific functions (implemented in sim_gpio.c or stm32_gpio.c) */
extern void PLATFORM_GPIO_Init(uint8_t pin, uint8_t mode);
extern void PLATFORM_GPIO_Write(uint8_t pin, GPIO_PinState state);
extern GPIO_PinState PLATFORM_GPIO_Read(uint8_t pin);

/* HAL implementations */
void HAL_GPIO_Init(uint8_t pin, GPIO_Mode mode) {
    PLATFORM_GPIO_Init(pin, mode);
}

void HAL_GPIO_WritePin(uint8_t pin, GPIO_PinState state) {
    PLATFORM_GPIO_Write(pin, state);
}

GPIO_PinState HAL_GPIO_ReadPin(uint8_t pin) {
    return PLATFORM_GPIO_Read(pin);
}