#if 1
#include "system_states.h"
#include "sensor_interface.h"
#include "pump_control.h"
#include "led_controller.h"
#include "button_handler.h"
#include "irrigation_config.h"
#include <stdio.h>
#include <time.h>

// Biến toàn cục
volatile SystemMode current_system_mode = MODE_AUTO;
IrrigationConfig system_config = {30, 70, 300}; // min, max, thời gian (s)

// Thêm biến để theo dõi thời gian tưới
static time_t watering_start_time = 0;
static uint8_t is_watering = 0;


// Hàm xử lý logic chính
void Main_Logic_Run(void) {
    SensorData sensor_data;
    uint8_t error_count = 0;
    
    printf("\n=== Starting Main Control Loop ===\n");
    
    while(1) {
        // Delay 1 giây (chỉ dùng 1 cơ chế)
        struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
        nanosleep(&ts, NULL);
        
        // Đọc cảm biến (giả lập giá trị thay đổi)
        Sensor_Read(&sensor_data);
        printf("[SENSOR] Moisture: %d%% (Threshold: %d%%)\n", 
               sensor_data.moisture, system_config.min_moisture);
        
        // Logic điều khiển AUTO
        if (current_system_mode == MODE_AUTO) {
            if (sensor_data.moisture < system_config.min_moisture && !is_watering) {
                Pump_SetState(true);  // Bật bơm khi độ ẩm < 30%
                is_watering = 1;
                watering_start_time = time(NULL);
                printf("[PUMP] AUTO ON (Low moisture)\n");
            }
            else if ((sensor_data.moisture > system_config.max_moisture || 
                     (time(NULL) - watering_start_time > system_config.max_watering_time)) 
                     && is_watering) {
                Pump_SetState(false);  // Tắt bơm khi đủ độ ẩm hoặc quá thời gian
                is_watering = 0;
                printf("[PUMP] AUTO OFF (Moisture OK/Timeout)\n");
            }
        }
        
        // Hiển thị trạng thái hiện tại
        printf("[SYSTEM] Pump: %s, Mode: %s\n\n",
               Pump_GetState() ? "ON" : "OFF",
               current_system_mode == MODE_AUTO ? "AUTO" : "MANUAL");
    }
    
}
/*
    * Hàm này sẽ chạy trong vòng lặp vô hạn, thực hiện các bước sau:
    * 1. Xử lý nút nhấn
    * 2. Đọc cảm biến
    * 3. Kiểm tra lỗi cảm biến
    * 4. Logic điều khiển tự động
    * 5. Cập nhật trạng thái LED
    * 6. Thông báo trạng thái hệ thống
    * 7. Tiết kiệm năng lượng với delay thông minh
void Main_Logic_Run(void) {
    SensorData sensor_data;
    uint8_t error_count = 0;
    
    printf("\n=== Starting Main Control Loop ===\n");
    
    while(1) {
        // Thêm dòng này để làm chậm tốc độ hiển thị
        struct timespec ts = {.tv_sec = 1, .tv_nsec = 0}; // Delay 1 giây
        nanosleep(&ts, NULL);




        // 1. Xử lý nút nhấn
        Button_Handler();
        
        // 2. Đọc cảm biến
        Sensor_Read(&sensor_data);
        printf("[SENSOR] Moisture: %d%%, Temp: %.1fC, Hum: %.1f%%\n",
               sensor_data.moisture, sensor_data.temperature, sensor_data.humidity);
        
        // 3. Kiểm tra lỗi cảm biến
        if(Sensor_CheckError()) {
            error_count++;
            printf("[ERROR] Sensor error count: %d/3\n", error_count);
            
            if(error_count > 3) {
                LED_UpdateState(LED_ERROR);
                Pump_SetState(false);
                printf("[SYSTEM] Critical sensor error! System halted.\n");
                continue; // Bỏ qua các bước tiếp theo
            }
        } else {
            error_count = 0;
        }
        
        // 4. Logic điều khiển tự động
        if(current_system_mode == MODE_AUTO) {
            // 4.1. Bắt đầu tưới nếu độ ẩm thấp và chưa đang tưới
            if(sensor_data.moisture < system_config.min_moisture && !is_watering) {
                Pump_SetState(true);
                LED_UpdateState(LED_WATERING);
                watering_start_time = time(NULL);
                is_watering = 1;
                printf("[AUTO] Start watering (Moisture too low)\n");
            }
            // 4.2. Dừng tưới nếu độ ẩm đủ hoặc quá thời gian
            else if((sensor_data.moisture > system_config.max_moisture || 
                    (time(NULL) - watering_start_time > system_config.max_watering_time)) 
                    && is_watering) {
                Pump_SetState(false);
                is_watering = 0;
                printf("[AUTO] Stop watering. ");
                printf("Watering duration: %ld seconds\n", time(NULL) - watering_start_time);
            }
        }
        
        // 5. Cập nhật trạng thái LED
        if(!is_watering) {
            if(sensor_data.moisture < system_config.min_moisture + 10) {
                LED_UpdateState(LED_LOW_MOISTURE_ALERT);
                printf("[STATUS] Low moisture alert (%d%%)\n", sensor_data.moisture);
            } else {
                LED_UpdateState(LED_NORMAL);
            }
        }
        
        // 6. Thông báo trạng thái hệ thống
        printf("[SYSTEM] Mode: %s, Pump: %s\n\n",
               current_system_mode == MODE_AUTO ? "AUTO" : "MANUAL",
               Pump_GetState() ? "ON" : "OFF");
        
        // 7. Tiết kiệm năng lượng với delay thông minh
        // Sử dụng hàm sleep thay vì vòng lặp busy-wait
        // volatile để ngăn compiler tối ưu
        volatile unsigned int i;
        for(i = 0; i < 500000; i++); // Giảm thời gian delay xuống 0.5s
    }
}

*/

#endif

#if 0
#include "system_states.h"
#include "sensor_interface.h"
#include "pump_control.h"
#include "led_controller.h"
#include "button_handler.h"
#include "irrigation_config.h"

// Biến toàn cục
volatile SystemMode current_system_mode = MODE_AUTO;
IrrigationConfig system_config = {30, 70, 300}; // min, max, thời gian (s)

// Hàm xử lý logic chính
void Main_Logic_Run(void) {
    SensorData sensor_data;
    uint8_t error_count = 0;
    
    while(1) {
        // 1. Xử lý nút nhấn
        Button_Handler();
        
        // 2. Đọc cảm biến
        Sensor_Read(&sensor_data);
        
        // 3. Kiểm tra lỗi cảm biến
        if(Sensor_CheckError()) {
            error_count++;
            if(error_count > 3) {
                LED_UpdateState(LED_ERROR);
                Pump_SetState(false);
                continue;
            }
        } else {
            error_count = 0;
        }
        
        // 4. Logic điều khiển tự động
        if(current_system_mode == MODE_AUTO) {
            if(sensor_data.moisture < system_config.min_moisture) {
                Pump_SetState(true);
                LED_UpdateState(LED_WATERING);
            } else if(sensor_data.moisture > system_config.max_moisture) {
                Pump_SetState(false);
                LED_UpdateState(sensor_data.moisture < system_config.min_moisture + 10 ? 
                               LED_LOW_MOISTURE_ALERT : LED_NORMAL);
            }
        }
        
        // 5. Tiết kiệm năng lượng
        // volatile để ngăn compiler tối ưu vòng lặp
        volatile uint32_t i;
        for(i = 0; i < 1000000; i++); // Delay
    }
}
#endif