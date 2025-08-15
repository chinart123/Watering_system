#if 1
//stage_B
#include "sensor_interface.h"
#include <stdlib.h>  // Cho hàm rand() và srand()
#include <time.h>    // Cho hàm time()
#include <stdio.h>   // Cho hàm printf()

static uint8_t sensor_error_flag = 0;  // Biến cờ báo lỗi cảm biến

void Sensor_Init(void) {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(time(NULL));
    
    // Đặt cờ lỗi về 0 (không lỗi)
    sensor_error_flag = 0;
    
    printf("[SENSOR] Initialized\n");
}

void Sensor_Read(SensorData* output) {
    static uint8_t initialized = 0;  // Biến kiểm tra đã khởi tạo chưa
    static uint8_t moisture = 60;    // Giá trị độ ẩm khởi tạo (60%)

    // Nếu chưa khởi tạo bộ sinh số ngẫu nhiên
    if (!initialized) {
        srand(time(NULL));  // Khởi tạo bằng thời gian hiện tại
        initialized = 1;    // Đánh dấu đã khởi tạo
    }

    // 1. Tạo thay đổi ngẫu nhiên cho độ ẩm
    // rand() % 61 tạo số từ 0-60
    // Trừ 30 để được khoảng -30 đến +30
    int change = (rand() % 61) - 30;
    
    // 2. Cập nhật giá trị độ ẩm
    moisture += change;
    
    // 3. Giới hạn độ ẩm trong khoảng 15-85%
    // Nếu dưới 15, gán = 15
    if (moisture < 15) {
        moisture = 15;
    }
    // Nếu trên 85, gán = 85
    else if (moisture > 85) {
        moisture = 85;
    }
    // Còn lại giữ nguyên giá trị
    
    // 4. Gán giá trị cho kết quả đầu ra
    output->moisture = moisture;
    
    // 5. Tạo nhiệt độ ngẫu nhiên (25-27°C)
    // rand() % 100: số từ 0-99
    // Chia 50.0: số thực từ 0.0-1.98
    // Cộng 25.0: 25.0-26.98
    output->temperature = 25.0f + (rand() % 100) / 50.0f;
    
    // 6. Tạo độ ẩm không khí ngẫu nhiên (60-62%)
    // Tương tự nhiệt độ
    output->humidity = 60.0f + (rand() % 100) / 50.0f;
}

uint8_t Sensor_CheckError(void) {
    // Trả về trạng thái lỗi (0 = không lỗi, 1 = có lỗi)
    return sensor_error_flag;
}
#endif
#if 0
//stage_A
#include "sensor_interface.h"
#include <stdio.h>
#include <time.h>

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

//support stage_B
void Sensor_Read(SensorData* output) {
    // Giả lập giá trị cảm biến ngẫu nhiên trong khoảng hợp lý
    static uint8_t moisture = 60; // Giá trị khởi tạo
    
    // Thay đổi độ ẩm mô phỏng
    if(rand() % 100 > 70) { // 30% chance thay đổi
        moisture += (rand() % 3) - 1; // Thay đổi -1 đến +1
        moisture = moisture > 100 ? 100 : moisture;
        moisture = moisture < 0 ? 0 : moisture;
    }
    
    output->moisture = moisture;
    output->temperature = 25.0f + (rand() % 100)/50.0f; // 25-27°C
    output->humidity = 60.0f + (rand() % 100)/50.0f; // 60-62%
}
#endif 