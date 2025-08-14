#pragma once
#include <stdint.h>

// Trạng thái hệ thống
typedef enum {
    MODE_AUTO,      // Chế độ tự động
    MODE_MANUAL     // Chế độ thủ công
} SystemMode;

// Trạng thái bơm
typedef enum {
    PUMP_OFF,       // Bơm tắt
    PUMP_ON         // Bơm hoạt động
} PumpState;

// Trạng thái LED
typedef enum {
    LED_NORMAL,             // Hoạt động bình thường
    LED_WATERING,           // Đang tưới nước
    LED_LOW_MOISTURE_ALERT, // Cảnh báo độ ẩm thấp
    LED_ERROR               // Lỗi hệ thống
} LedState;

// Cấu trúc dữ liệu cảm biến
typedef struct {
    volatile float temperature; // volatile vì dữ liệu thay đổi từ bên ngoài
    volatile float humidity;
    volatile uint8_t moisture; 
} SensorData;

// Cấu hình hệ thống
typedef struct {
    uint8_t min_moisture;       // Ngưỡng độ ẩm tối thiểu
    uint8_t max_moisture;       // Ngưỡng độ ẩm tối đa
    uint16_t max_watering_time; // Thời gian tưới tối đa
} IrrigationConfig;