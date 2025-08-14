#include "led_controller.h"
#include <stdio.h>

// Ánh xạ trạng thái LED sang chuỗi (hạn chế dùng flash)
static const char* const led_state_strings[] = {
    [LED_NORMAL] = "NORMAL",
    [LED_WATERING] = "WATERING",
    [LED_LOW_MOISTURE_ALERT] = "LOW MOISTURE",
    [LED_ERROR] = "ERROR"
};

void LED_Init(void) {
    printf("[LED] Initialized\n");
}

void LED_UpdateState(LedState state) {
    // Chỉ dùng enum để tiết kiệm bộ nhớ
    printf("[LED] State: %s\n", led_state_strings[state]);
}