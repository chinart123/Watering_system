#if 1
#include "button_handler.h"
#include "irrigation_config.h"
#include <stdio.h>
#include <unistd.h> // Thêm thư viện này cho hàm usleep

// Biến volatile vì thay đổi từ ngắt
static volatile uint8_t button1_state = 0;
static volatile uint8_t button2_state = 0;

void Button_Handler(void) {
    static uint8_t counter = 0;
    static uint32_t last_press_time = 0;
    
    // Giả lập nút nhấn mỗi 3 giây (thay vì liên tục)
    if(counter++ >= 30) { // Giảm tốc độ thay đổi
        counter = 0;
        button1_state = !button1_state;
        
        // Chống dội nút (debounce)
        usleep(100000); // 100ms
        
        // Chỉ chuyển chế độ khi ở trạng thái nhấn (1)
        if(button1_state == 1) {
            current_system_mode = (current_system_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
            printf("[BUTTON] Mode changed to %s\n", 
                  current_system_mode == MODE_AUTO ? "AUTO" : "MANUAL");
        }
    }
}

uint8_t Button_GetState(uint8_t button_id) {
    return (button_id == 1) ? button1_state : button2_state;
}
#endif

#if 0
// stage A 
// #include "button_handler.h"
// #include "irrigation_config.h"
// #include <stdio.h>

// // Biến volatile vì thay đổi từ ngắt
// static volatile uint8_t button1_state = 0;
// static volatile uint8_t button2_state = 0;

// void Button_Handler(void) {
//     // Mô phỏng xử lý nút nhấn
//     static uint8_t counter = 0;
    
//     if(counter++ >= 10) {
//         button1_state = !button1_state;
//         counter = 0;
        
//         // Chuyển chế độ khi nhấn nút 1
//         current_system_mode = (current_system_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
//         printf("[BUTTON] Mode changed to %s\n", 
//               current_system_mode == MODE_AUTO ? "AUTO" : "MANUAL");
//     }
// }

// uint8_t Button_GetState(uint8_t button_id) {
//     return (button_id == 1) ? button1_state : button2_state;
// }
#endif 