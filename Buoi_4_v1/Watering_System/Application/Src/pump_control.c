#include "pump_control.h"
#include "system_states.h"
#include <stdio.h>

// Biến static - chỉ truy cập trong file này
static bool pump_status = false;

void Pump_Init(void) {
    pump_status = false;
    printf("[PUMP] Initialized\n");
}

void Pump_SetState(bool state) {
    pump_status = state;
    printf("[PUMP] %s\n", state ? "ACTIVATED" : "DEACTIVATED");
}

bool Pump_GetState(void) {
    return pump_status;
}