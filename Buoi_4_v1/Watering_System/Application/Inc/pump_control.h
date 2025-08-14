#pragma once
#include <stdbool.h>

// Khởi tạo bơm
void Pump_Init(void);

// Điều khiển bơm
void Pump_SetState(bool state);

// Kiểm tra trạng thái bơm
bool Pump_GetState(void);