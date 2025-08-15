/* Watering_System/Core/Inc/HAL/hal_gpio.h */
#pragma once
#include <stdint.h>

/* GPIO Pin States */
typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} GPIO_PinState;

/* GPIO Modes */
typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT
} GPIO_Mode;

/**
  * @brief Initialize GPIO pin
  * @param pin: Pin number (platform-specific)
  * @param mode: GPIO mode (input/output)
  */
void HAL_GPIO_Init(uint8_t pin, GPIO_Mode mode);

/**
  * @brief Write to GPIO pin
  * @param pin: Pin number
  * @param state: Pin state (SET/RESET)
  */
void HAL_GPIO_WritePin(uint8_t pin, GPIO_PinState state);

/**
  * @brief Read GPIO pin state
  * @param pin: Pin number
  * @return Current pin state
  */
GPIO_PinState HAL_GPIO_ReadPin(uint8_t pin);