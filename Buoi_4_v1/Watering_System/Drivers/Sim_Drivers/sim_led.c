#include "sim_led.h"
#include <stdio.h>

void SimLED_SetState(int state) {
    const char* states[] = {"NORMAL", "WATERING", "LOW MOISTURE", "ERROR"};
    printf("[SIM] LED: %s\n", states[state]);
}