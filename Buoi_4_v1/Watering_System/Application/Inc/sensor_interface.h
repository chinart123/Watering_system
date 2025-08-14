#pragma once
#include "system_states.h"

// Khởi tạo cảm biến
void Sensor_Init(void);

// Đọc dữ liệu cảm biến
void Sensor_Read(SensorData* output);

// Kiểm tra lỗi cảm biến
uint8_t Sensor_CheckError(void);