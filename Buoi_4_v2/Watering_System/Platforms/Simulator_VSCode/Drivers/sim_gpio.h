/* Watering_System/Platforms/Simulator_VSCode/Drivers/sim_gpio.h */
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} GPIO_PinState;

typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT
} GPIO_Mode;

void PLATFORM_GPIO_Init(uint8_t pin, uint8_t mode);
void PLATFORM_GPIO_Write(uint8_t pin, GPIO_PinState state);
GPIO_PinState PLATFORM_GPIO_Read(uint8_t pin);