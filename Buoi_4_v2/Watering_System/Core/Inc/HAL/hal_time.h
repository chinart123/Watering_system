/* Watering_System/Core/Inc/HAL/hal_time.h */
#pragma once
#include <stdint.h>

/**
  * @brief Delay function
  * @param ms Delay time in milliseconds
  */
void HAL_Delay(uint32_t ms);

/**
  * @brief Get system tick
  * @return Current tick count in milliseconds
  */
uint32_t HAL_GetTick(void);