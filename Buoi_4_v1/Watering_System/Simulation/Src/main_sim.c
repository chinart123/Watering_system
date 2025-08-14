#include "system_states.h"
#include "sensor_interface.h"
#include "pump_control.h"
#include "led_controller.h"
#include "button_handler.h"
#include "irrigation_config.h"
#include <stdio.h>

// Khai báo nguyên mẫu hàm thay vì include header không tồn tại
void Main_Logic_Run(void);

int main() {
    printf("\n=== AUTOMATIC IRRIGATION SYSTEM SIMULATION ===\n");
    printf("Initializing system...\n");
    
    // Khởi tạo các module
    Sensor_Init();
    Pump_Init();
    LED_Init();
    
    printf("Starting main loop...\n");
    printf("----------------------------------------\n");
    
    // Chạy logic chính
    Main_Logic_Run();
    
    return 0;
}