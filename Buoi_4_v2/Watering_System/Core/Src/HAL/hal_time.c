/* Watering_System/Core/Src/HAL/hal_time.c */
#include "hal_time.h"

/* Platform-specific implementation */
extern uint32_t PLATFORM_GetTick(void);
extern void PLATFORM_Delay(uint32_t ms);

void HAL_Delay(uint32_t ms) {
    PLATFORM_Delay(ms);
}

uint32_t HAL_GetTick(void) {
    return PLATFORM_GetTick();
}