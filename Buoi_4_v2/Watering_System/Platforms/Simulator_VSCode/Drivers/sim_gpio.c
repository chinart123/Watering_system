#if 1
/* Watering_System/Platforms/Simulator_VSCode/Drivers/sim_gpio.c */
#include "sim_gpio.h"
#include <stdio.h>
#include <stdbool.h>

#define MAX_PINS 16

static GPIO_PinState pin_states[MAX_PINS] = {GPIO_PIN_RESET};
static GPIO_Mode pin_modes[MAX_PINS] = {GPIO_MODE_INPUT};

void PLATFORM_GPIO_Init(uint8_t pin, uint8_t mode) {
    if (pin >= MAX_PINS) return;
    
    pin_modes[pin] = mode;
    printf("[GPIO] Pin %d initialized as %s\n", 
           pin, 
           mode == GPIO_MODE_INPUT ? "INPUT" : "OUTPUT");
}

void PLATFORM_GPIO_Write(uint8_t pin, GPIO_PinState state) {
    if (pin >= MAX_PINS || pin_modes[pin] != GPIO_MODE_OUTPUT) return;
    
    pin_states[pin] = state;
    printf("[GPIO] Write pin %d -> %s\n", 
           pin, 
           state == GPIO_PIN_SET ? "HIGH" : "LOW");
}

GPIO_PinState PLATFORM_GPIO_Read(uint8_t pin) {
    if (pin >= MAX_PINS) return GPIO_PIN_RESET;
    
    // Log chỉ khi đọc từ nút nhấn
    if (pin == 0 || pin == 1) {
        printf("[GPIO] Read pin %d: %s\n", 
               pin, 
               pin_states[pin] == GPIO_PIN_SET ? "PRESSED" : "RELEASED");
    }
    
    return pin_states[pin];
}


#endif
#if 0
/* Watering_System/Platforms/Simulator_VSCode/Drivers/sim_gpio.c */
#include "sim_gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include "hal_time.h"

#define MAX_PINS 16

static GPIO_PinState pin_states[MAX_PINS] = {GPIO_PIN_RESET};
static GPIO_Mode pin_modes[MAX_PINS] = {GPIO_MODE_INPUT};

void PLATFORM_GPIO_Init(uint8_t pin, uint8_t mode) {
    if (pin >= MAX_PINS) return;
    
    pin_modes[pin] = mode;
    printf("[GPIO] Pin %d initialized as %s\n", 
           pin, 
           mode == GPIO_MODE_INPUT ? "INPUT" : "OUTPUT");
}

void PLATFORM_GPIO_Write(uint8_t pin, GPIO_PinState state) {
    if (pin >= MAX_PINS || pin_modes[pin] != GPIO_MODE_OUTPUT) return;
    
    pin_states[pin] = state;
    printf("[GPIO] Write pin %d -> %s\n", 
           pin, 
           state == GPIO_PIN_SET ? "HIGH" : "LOW");
}

GPIO_PinState PLATFORM_GPIO_Read(uint8_t pin) {
    if (pin >= MAX_PINS) return GPIO_PIN_RESET;
    return pin_states[pin];
}
#endif
#if 0
/* Watering_System/Platforms/Simulator_VSCode/Drivers/sim_gpio.c */
#include "sim_gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include "hal_time.h"

#define MAX_PINS 16
#define BUTTON_PIN 1  // Thêm define cho BUTTON_PIN

static GPIO_PinState pin_states[MAX_PINS] = {GPIO_PIN_RESET};
static GPIO_Mode pin_modes[MAX_PINS] = {GPIO_MODE_INPUT};
static bool button_pressed = false;

void PLATFORM_GPIO_Init(uint8_t pin, uint8_t mode) {
    if (pin >= MAX_PINS) return;
    
    pin_modes[pin] = mode;
    printf("[GPIO] Pin %d initialized as %s\n", 
           pin, 
           mode == GPIO_MODE_INPUT ? "INPUT" : "OUTPUT");
}

void PLATFORM_GPIO_Write(uint8_t pin, GPIO_PinState state) {
    if (pin >= MAX_PINS || pin_modes[pin] != GPIO_MODE_OUTPUT) return;
    
    pin_states[pin] = state;
    printf("[GPIO] Write pin %d -> %s\n", 
           pin, 
           state == GPIO_PIN_SET ? "HIGH" : "LOW");
}

GPIO_PinState PLATFORM_GPIO_Read(uint8_t pin) {
    if (pin >= MAX_PINS) return GPIO_PIN_RESET;
    
    // Simulate button press on pin 1
    if (pin == BUTTON_PIN) {
        // For demo purposes, alternate button state every 2 seconds
        uint32_t current_time = HAL_GetTick();
        button_pressed = (current_time / 2000) % 2;
        
        printf("[GPIO] Read pin %d (button): %s\n", 
               pin, 
               button_pressed ? "PRESSED" : "RELEASED");
        return button_pressed ? GPIO_PIN_SET : GPIO_PIN_RESET;
    }
    
    printf("[GPIO] Read pin %d -> %s\n", 
           pin, 
           pin_states[pin] == GPIO_PIN_SET ? "HIGH" : "LOW");
    return pin_states[pin];
}
#endif    