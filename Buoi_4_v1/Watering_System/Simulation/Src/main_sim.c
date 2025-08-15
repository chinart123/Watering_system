#include "system_states.h"
#include "sensor_interface.h"
#include "pump_control.h"
#include "led_controller.h"
#include "button_handler.h"
#include "irrigation_config.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Thêm phần kiểm tra hệ điều hành
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void some_function() {
    // Thay sleep(1) bằng:
    #ifdef _WIN32
        Sleep(1000);  // Windows
    #else
        sleep(1);     // Linux/Mac
    #endif
}


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
    sleep(1); // Dừng 1 giây
    // Chạy logic chính
    Main_Logic_Run();
    
    return 0;
}