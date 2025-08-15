/* Watering_System/Platforms/Simulator_VSCode/Drivers/sim_time.c */
#include "sim_time.h"  // Đổi từ sim_time.h" thành "sim_time.h"
#include <time.h>
#include <unistd.h>

static uint32_t startup_time = 0;

void PLATFORM_Delay(uint32_t ms) {
    sleep(ms * 1000); // Convert ms to microseconds
}

uint32_t PLATFORM_GetTick(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    
    if (startup_time == 0) {
        startup_time = (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
        return 0;
    }
    
    return ((ts.tv_sec * 1000) + (ts.tv_nsec / 1000000)) - startup_time;
}