#include "sim_dht11.h"
#include <time.h>    // Thêm thư viện này cho hàm time()
#include <stdlib.h>  // Thêm thư viện này cho hàm rand()
void SimSensor_Read(uint8_t* data) {
    data[0] = 50 + rand() % 30; // Moisture: 50-80%
    data[1] = 25 + rand() % 5;  // Temp: 25-30°C
    data[2] = 60 + rand() % 20; // Humidity: 60-80%
}