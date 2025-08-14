#include "sim_dht11.h"
#include <stdio.h>

void SimSensor_Read(uint8_t* data) {
    printf("[SIM] Sensor data read\n");
    data[0] = 50; // moisture
    data[1] = 25; // temp
    data[2] = 60; // humidity
}