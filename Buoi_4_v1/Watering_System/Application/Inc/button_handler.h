#include <stdint.h>
#pragma once

// Xử lý nút nhấn
void Button_Handler(void);

// Lấy trạng thái nút
uint8_t Button_GetState(uint8_t button_id);