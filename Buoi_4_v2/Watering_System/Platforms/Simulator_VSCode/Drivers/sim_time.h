/* Watering_System/Platforms/Simulator_VSCode/Drivers/sim_time.h */
#pragma once
#include <stdint.h>

uint32_t PLATFORM_GetTick(void);
void PLATFORM_Delay(uint32_t ms);