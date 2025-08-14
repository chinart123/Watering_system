#include "sim_pump.h"
#include <stdio.h>

void SimPump_SetState(int state) {
    printf("[SIM] Pump %s\n", state ? "ON" : "OFF");
}