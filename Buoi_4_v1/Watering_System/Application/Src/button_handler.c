#include "button_handler.h"
#include "irrigation_config.h"
#include <stdio.h>

// Biến volatile vì thay đổi từ ngắt
static volatile uint8_t button1_state = 0;
static volatile uint8_t button2_state = 0;

void Button_Handler(void) {
    // Mô phỏng xử lý nút nhấn
    static uint8_t counter = 0;
    
    if(counter++ >= 10) {
        button1_state = !button1_state;
        counter = 0;
        
        // Chuyển chế độ khi nhấn nút 1
        current_system_mode = (current_system_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        printf("[BUTTON] Mode changed to %s\n", 
              current_system_mode == MODE_AUTO ? "AUTO" : "MANUAL");
    }
}

uint8_t Button_GetState(uint8_t button_id) {
    return (button_id == 1) ? button1_state : button2_state;
}