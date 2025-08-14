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