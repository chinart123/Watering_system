#pragma once
#include "system_states.h"

// Biến toàn cục - extern để chia sẻ giữa các module
extern volatile SystemMode current_system_mode;
extern IrrigationConfig system_config;

// Khởi tạo cấu hình
void Config_Init(void);