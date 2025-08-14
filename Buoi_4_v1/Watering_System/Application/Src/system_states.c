#include "system_states.h"

// Biến static - chỉ truy cập trong file này
static PumpState current_pump_state = PUMP_OFF;
static LedState current_led_state = LED_NORMAL;

// Hàm getter cho các module khác
PumpState Get_PumpState(void) {
    return current_pump_state;
}

void Set_PumpState(PumpState state) {
    current_pump_state = state;
}

LedState Get_LedState(void) {
    return current_led_state;
}

void Set_LedState(LedState state) {
    current_led_state = state;
}