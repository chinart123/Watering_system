#include "sensor_interface.h"
#include <stdio.h>

// Union để tối ưu bộ nhớ và xử lý padding
typedef union {
    struct {
        uint8_t header;
        uint8_t moisture;
        uint8_t temp;
        uint8_t hum;
        uint8_t checksum;
    } data;
    uint8_t raw[5];
} SensorPacket;

void Sensor_Init(void) {
    printf("[SENSOR] Initialized\n");
}

void Sensor_Read(SensorData* output) {
    // Mô phỏng đọc dữ liệu cảm biến
    static SensorPacket packet = {
        .data = {0xAA, 50, 25, 60, 0x55}
    };
    
    // Sử dụng union để tránh vấn đề padding
    output->moisture = packet.data.moisture;
    output->temperature = packet.data.temp;
    output->humidity = packet.data.hum;
}

uint8_t Sensor_CheckError(void) {
    // 0 = không lỗi, 1 = lỗi
    return 0;
}

