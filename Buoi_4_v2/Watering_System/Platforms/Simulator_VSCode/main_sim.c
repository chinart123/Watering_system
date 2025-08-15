#if 1
/* Watering_System/Platforms/Simulator_VSCode/main_sim.c */
#include "hal_gpio.h"
#include "hal_time.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// ========================
// Định nghĩa các MACRO
// ========================

// Ngưỡng độ ẩm
#define MOISTURE_RED_THRESHOLD    20.0f   // Dưới 20%: Báo đỏ
#define MOISTURE_GREEN_THRESHOLD  50.0f   // Trên 50%: Báo xanh
// Giữa 20-50%: Báo vàng

// Chân GPIO (theo hardware_map.md)
#define BUTTON_1_PIN      0   // PA0 - Mode Toggle
#define BUTTON_2_PIN      1   // PA1 - Manual Watering
#define LED_PIN_GREEN     8   // PB0
#define LED_PIN_RED       9   // PB1
#define LED_PIN_YELLOW    10  // PB2

// Thời gian
#define BUTTON_DEBOUNCE_MS     250
#define AUTO_UPDATE_INTERVAL   5000    // 5 giây
#define WATERING_RATE          0.5f    // 0.5% moisture/s

// ========================
// Biến toàn cục
// ========================
typedef enum { MODE_AUTO, MODE_MANUAL } SystemMode;

static SystemMode current_mode = MODE_AUTO;
static float simulated_moisture = 50.0f;
static bool auto_mode_enabled = true;

// ========================
// Hàm cập nhật LED
// ========================
void update_led_state() {
    if (simulated_moisture < MOISTURE_RED_THRESHOLD) {
        // LED Đỏ - Ngưỡng nguy hiểm
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_RESET);
        printf("[LED] State: RED (Low Moisture Alert)\n");
        
        // Tự động chuyển sang MODE_AUTO
        current_mode = MODE_AUTO;  
    } 
    else if (simulated_moisture >= MOISTURE_GREEN_THRESHOLD) {
        // LED Xanh - Ngưỡng tối ưu
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_SET);
        printf("[LED] State: GREEN (Normal)\n");
    } 
    else {
        // LED Vàng - Ngưỡng cảnh báo
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_RESET);
        printf("[LED] State: YELLOW (Sufficient)\n");
    }
}

// ========================
// Hàm xử lý nút nhấn
// ========================
void handle_buttons(GPIO_PinState button1_state, GPIO_PinState button2_state) {
    static uint32_t last_button1_time = 0;
    static uint32_t last_button2_time = 0;

    // Nút 1: Chuyển mode (chỉ khi độ ẩm > ngưỡng đỏ)
    if (button1_state == GPIO_PIN_SET && 
        (HAL_GetTick() - last_button1_time > BUTTON_DEBOUNCE_MS) &&
        simulated_moisture >= MOISTURE_RED_THRESHOLD) 
    {
        current_mode = (current_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        printf("[System] Mode changed to: %s\n", 
              (current_mode == MODE_MANUAL) ? "MANUAL" : "AUTO");
        last_button1_time = HAL_GetTick();
    }
    
    // Nút 2: Tưới thủ công (chỉ trong MODE_MANUAL)
    if (button2_state == GPIO_PIN_SET && 
        current_mode == MODE_MANUAL &&
        HAL_GetTick() - last_button2_time > BUTTON_DEBOUNCE_MS) 
    {
        printf("[System] Manual watering activated! +15%% moisture\n");
        simulated_moisture += 15.0f;
        if (simulated_moisture > 100) simulated_moisture = 100;
        last_button2_time = HAL_GetTick();
    }
}

// ========================
// Hàm hiển thị trạng thái
// ========================
void display_system_status() {
    printf("\n--- SYSTEM STATUS ---\n");
    printf("Current Mode:    %s\n", current_mode == MODE_AUTO ? "AUTO" : "MANUAL");
    printf("Moisture Level:  %.1f%%\n", simulated_moisture);
    printf("Auto Mode:       %s\n", auto_mode_enabled ? "ENABLED" : "DISABLED");
    printf("Red Threshold:   < %.1f%%\n", MOISTURE_RED_THRESHOLD);
    printf("Green Threshold: > %.1f%%\n", MOISTURE_GREEN_THRESHOLD);
    printf("----------------------\n");
}

// ========================
// Hàm chế độ tự động
// ========================
void handle_auto_mode() {
    static uint32_t last_update = 0;
    
    if (auto_mode_enabled && 
        (HAL_GetTick() - last_update > AUTO_UPDATE_INTERVAL)) 
    {
        // Giảm độ ẩm ngẫu nhiên
        float decrease = (rand() % 100) / 10.0f; // 0-10%
        simulated_moisture -= decrease;
        if (simulated_moisture < 0) simulated_moisture = 0;
        
        printf("[AUTO] Moisture decreased by %.1f%% (now %.1f%%)\n", 
               decrease, simulated_moisture);
        
        last_update = HAL_GetTick();
    }
}

// ========================
// Hàm main
// ========================
int main() {
    srand(time(NULL));
    
    printf("Starting Advanced Simulation (Macro Version)...\n");
    printf("Controls:\n");
    printf("  1 - Toggle Mode\n");
    printf("  2 - Manual Watering\n");
    printf("  3 - Toggle Auto Moisture Change\n");
    printf("  4 - Add Moisture (+10%%)\n");
    printf("  5 - Remove Moisture (-10%%)\n");
    printf("LED Thresholds: RED < %.1f%%, GREEN > %.1f%%\n\n", 
          MOISTURE_RED_THRESHOLD, MOISTURE_GREEN_THRESHOLD);
    
    // Khởi tạo GPIO
    HAL_GPIO_Init(LED_PIN_GREEN, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(LED_PIN_YELLOW, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(LED_PIN_RED, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(BUTTON_1_PIN, GPIO_MODE_INPUT);
    HAL_GPIO_Init(BUTTON_2_PIN, GPIO_MODE_INPUT);
    
    // Trạng thái ban đầu
    update_led_state();
    display_system_status();
    
    while(1) {
        printf("\nEnter command: ");
        int c = getchar();
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer

        GPIO_PinState button1_state = GPIO_PIN_RESET;
        GPIO_PinState button2_state = GPIO_PIN_RESET;
        
        switch (c) {
            case '1': button1_state = GPIO_PIN_SET; break;
            case '2': button2_state = GPIO_PIN_SET; break;
            case '3': 
                auto_mode_enabled = !auto_mode_enabled;
                printf("[System] Auto moisture change %s\n",
                      auto_mode_enabled ? "ENABLED" : "DISABLED");
                break;
            case '4': 
                simulated_moisture += 10.0f;
                if (simulated_moisture > 100) simulated_moisture = 100;
                printf("[System] Added 10%% moisture (now %.1f%%)\n", simulated_moisture);
                break;
            case '5': 
                simulated_moisture -= 10.0f;
                if (simulated_moisture < 0) simulated_moisture = 0;
                printf("[System] Removed 10%% moisture (now %.1f%%)\n", simulated_moisture);
                break;
            default:
                printf("Invalid command! Valid options: 1, 2, 3, 4, 5\n");
                continue;
        }
        
        // Xử lý chế độ tự động
        handle_auto_mode();
        
        // Cập nhật trạng thái
        handle_buttons(button1_state, button2_state);
        update_led_state();
        display_system_status();
    }
    
    return 0;
}

#endif 
#if 0
//main_sim.c version 3: Thay dodi
/* Watering_System/Platforms/Simulator_VSCode/main_sim.c */
#include "hal_gpio.h"
#include "hal_time.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Định nghĩa các hằng số
#define BUTTON_1_PIN    0
#define BUTTON_2_PIN    1
#define LED_PIN_GREEN   8
#define LED_PIN_RED     9
#define LED_PIN_YELLOW  10

// Trạng thái hệ thống
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

// Biến toàn cục
static SystemMode current_mode = MODE_AUTO;
static float simulated_moisture = 50.0f;
static bool auto_mode_enabled = true;

// Hàm cập nhật LED
void update_led_state() {
    if (simulated_moisture < 20.0f) {
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_RESET);
        printf("[LED] State: RED (Low Moisture Alert)\n");
        current_mode = MODE_AUTO;  // Luôn chuyển sang AUTO khi độ ẩm thấp
    } else if (simulated_moisture >= 50.0f) {
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_SET);
        printf("[LED] State: GREEN (Normal)\n");
    } else {
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_RESET);
        printf("[LED] State: YELLOW (Sufficient)\n");
    }
}

// Hàm xử lý nút nhấn
void handle_buttons(GPIO_PinState button1_state, GPIO_PinState button2_state) {
    static uint32_t last_button1_time = 0;
    static uint32_t last_button2_time = 0;

    // Xử lý Nút 1: Chuyển đổi chế độ
    if (button1_state == GPIO_PIN_SET && (HAL_GetTick() - last_button1_time > 250)) {
        if (simulated_moisture >= 20.0f) {
            current_mode = (current_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
            printf("[System] Mode changed to: %s\n", 
                  (current_mode == MODE_MANUAL) ? "MANUAL" : "AUTO");
            last_button1_time = HAL_GetTick();
        }
    }
    
    // Xử lý Nút 2: Tưới thủ công
    if (button2_state == GPIO_PIN_SET && current_mode == MODE_MANUAL) {
        if (HAL_GetTick() - last_button2_time > 250) {
            printf("[System] Manual watering activated! +15%% moisture\n");
            simulated_moisture += 15.0f;
            if (simulated_moisture > 100) simulated_moisture = 100;
            last_button2_time = HAL_GetTick();
        }
    }
}

// Hàm hiển thị trạng thái hệ thống
void display_system_status() {
    printf("\n--- SYSTEM STATUS ---\n");
    printf("Current Mode:    %s\n", current_mode == MODE_AUTO ? "AUTO" : "MANUAL");
    printf("Moisture Level:  %.1f%%\n", simulated_moisture);
    printf("Auto Mode:       %s\n", auto_mode_enabled ? "ENABLED" : "DISABLED");
    printf("----------------------\n");
}

// Hàm xử lý chế độ tự động
void handle_auto_mode() {
    static uint32_t last_update = 0;
    if (HAL_GetTick() - last_update > 5000) {  // Cập nhật mỗi 5 giây
        // Giảm độ ẩm ngẫu nhiên 0-10%
        float decrease = (rand() % 100) / 10.0f;
        simulated_moisture -= decrease;
        if (simulated_moisture < 0) simulated_moisture = 0;
        
        printf("[AUTO] Moisture decreased by %.1f%% (now %.1f%%)\n", 
               decrease, simulated_moisture);
        
        last_update = HAL_GetTick();
    }
}

int main() {
    // Khởi tạo seed ngẫu nhiên
    srand(time(NULL));
    
    printf("Starting Advanced Simulation...\n");
    printf("Controls:\n");
    printf("  1 - Toggle Mode\n");
    printf("  2 - Manual Watering\n");
    printf("  3 - Toggle Auto Moisture Change\n");
    printf("  4 - Add Moisture (+10%%)\n");
    printf("  5 - Remove Moisture (-10%%)\n\n");
    
    // Khởi tạo GPIO
    HAL_GPIO_Init(LED_PIN_GREEN, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(LED_PIN_YELLOW, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(LED_PIN_RED, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(BUTTON_1_PIN, GPIO_MODE_INPUT);
    HAL_GPIO_Init(BUTTON_2_PIN, GPIO_MODE_INPUT);
    
    // Trạng thái ban đầu
    update_led_state();
    display_system_status();
    
    while(1) {
        printf("\nEnter command: ");
        int c = getchar();
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // Xóa bộ đệm

        GPIO_PinState button1_state = GPIO_PIN_RESET;
        GPIO_PinState button2_state = GPIO_PIN_RESET;
        
        switch (c) {
            case '1':
                button1_state = GPIO_PIN_SET;
                break;
            case '2':
                button2_state = GPIO_PIN_SET;
                break;
            case '3':
                auto_mode_enabled = !auto_mode_enabled;
                printf("[System] Auto moisture change %s\n",
                      auto_mode_enabled ? "ENABLED" : "DISABLED");
                break;
            case '4':
                simulated_moisture += 10.0f;
                if (simulated_moisture > 100) simulated_moisture = 100;
                printf("[System] Added 10%% moisture (now %.1f%%)\n", simulated_moisture);
                break;
            case '5':
                simulated_moisture -= 10.0f;
                if (simulated_moisture < 0) simulated_moisture = 0;
                printf("[System] Removed 10%% moisture (now %.1f%%)\n", simulated_moisture);
                break;
            default:
                printf("Invalid command! Valid options: 1, 2, 3, 4, 5\n");
                continue;
        }
        
        // Xử lý chế độ tự động nếu được bật
        if (auto_mode_enabled) {
            handle_auto_mode();
        }
        
        // Cập nhật trạng thái
        handle_buttons(button1_state, button2_state);
        update_led_state();
        display_system_status();
    }
    
    return 0;
}


#endif


#if 0
/* Watering_System/Platforms/Simulator_VSCode/main_sim.c */
#include "hal_gpio.h"
#include "hal_time.h"
#include <stdio.h>
#include <stdbool.h>

// Định nghĩa các hằng số cho GPIO theo hardware_map.md
#define BUTTON_1_PIN    0 // PA0
#define BUTTON_2_PIN    1 // PA1
#define LED_PIN_GREEN   8 // PB0
#define LED_PIN_RED     9 // PB1
#define LED_PIN_YELLOW  10 // PB2

// Định nghĩa trạng thái hệ thống
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

// Biến trạng thái hệ thống
static SystemMode current_mode = MODE_AUTO;
static float simulated_moisture = 50.0f; // Độ ẩm ban đầu

// Hàm cập nhật trạng thái LED
void update_led_state() {
    // Độ ẩm quá thấp, báo đỏ và chuyển sang chế độ tự động
    if (simulated_moisture < 20.0f) {
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_RESET);
        printf("[LED] State: RED (Low Moisture Alert)\n");
        current_mode = MODE_AUTO;
    }
    // Độ ẩm vừa đủ, báo xanh lá hoặc vàng
    else if (simulated_moisture >= 50.0f) {
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_SET);
        printf("[LED] State: GREEN (Normal Operation)\n");
    }
    else {
        HAL_GPIO_WritePin(LED_PIN_RED, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PIN_YELLOW, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PIN_GREEN, GPIO_PIN_RESET);
        printf("[LED] State: YELLOW (Sufficient Moisture)\n");
    }
}

// Hàm xử lý nút nhấn
void handle_buttons(GPIO_PinState button1_state, GPIO_PinState button2_state) {
    static uint32_t last_button1_time = 0;
    static uint32_t last_button2_time = 0;

    // Xử lý Nút 1: Chuyển đổi chế độ
    if (button1_state == GPIO_PIN_SET && (HAL_GetTick() - last_button1_time > 250)) {
        if (simulated_moisture >= 20.0f) {
            current_mode = (current_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
            printf("[System] Mode changed to: %s\n", (current_mode == MODE_MANUAL) ? "MANUAL" : "AUTO");
            last_button1_time = HAL_GetTick();
        } else {
            printf("[System] Cannot change mode. Moisture is too low. Sticking to AUTO.\n");
        }
    }
    
    // Xử lý Nút 2: Tưới thủ công
    if (button2_state == GPIO_PIN_SET && current_mode == MODE_MANUAL) {
        if (HAL_GetTick() - last_button2_time > 250) {
            printf("[System] Manual watering activated!\n");
            // Logic bật bơm
            last_button2_time = HAL_GetTick();
        }
    }
}

int main() {
    printf("Starting Simulation...\n");
    printf("Enter '1' to simulate Button 1 (Mode Toggle) or '2' to simulate Button 2 (Manual Watering).\n");
    
    // Initialize hardware (mô phỏng)
    HAL_GPIO_Init(LED_PIN_GREEN, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(LED_PIN_YELLOW, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(LED_PIN_RED, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(BUTTON_1_PIN, GPIO_MODE_INPUT);
    HAL_GPIO_Init(BUTTON_2_PIN, GPIO_MODE_INPUT);
    
    while(1) {
        int c = getchar();
        if (c != EOF) {
            GPIO_PinState button1_state = (c == '1') ? GPIO_PIN_SET : GPIO_PIN_RESET;
            GPIO_PinState button2_state = (c == '2') ? GPIO_PIN_SET : GPIO_PIN_RESET;

            // Xóa bộ đệm bàn phím
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            
            // Xử lý logic
            update_led_state();
            handle_buttons(button1_state, button2_state);
        }
    }
    
    return 0;
}
#endif 

#if 0
/* Watering_System/Platforms/Simulator_VSCode/main_sim.c */
#include "hal_gpio.h"
#include "hal_time.h"
#include <stdio.h>
#include <stdbool.h>  // Thêm thư viện cho bool

#define LED_PIN     0
#define BUTTON_PIN  1

int main() {
    printf("Starting Simulation...\n");
    
    // Initialize hardware
    HAL_GPIO_Init(LED_PIN, GPIO_MODE_OUTPUT);
    HAL_GPIO_Init(BUTTON_PIN, GPIO_MODE_INPUT);
    
    uint32_t last_blink = HAL_GetTick();
    bool led_state = false;
    
    while(1) {
    if (HAL_GetTick() - last_blink >= 500) {
        led_state = !led_state;
        HAL_GPIO_WritePin(LED_PIN, led_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
        last_blink = HAL_GetTick();
        printf("LED state: %s\n", led_state ? "ON" : "OFF");
        fflush(stdout);  // <-- Thêm dòng này
    }
    
    if (HAL_GPIO_ReadPin(BUTTON_PIN) == GPIO_PIN_SET) {
        printf("Button pressed!\n");
        fflush(stdout);  // <-- Và dòng này
        HAL_Delay(200);
    }
    
    HAL_Delay(10);
}
    
    return 0;
}
#endif
