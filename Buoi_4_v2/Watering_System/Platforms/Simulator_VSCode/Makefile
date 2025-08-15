# Compiler và flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g \
         -I../../Core/Inc -I../../Core/Inc/HAL -I./Drivers \
         -D_POSIX_C_SOURCE=200809L

# Source files
SRC_DIR = .
DRIVERS_DIR = ./Drivers
HAL_DIR = ../../Core/Src/HAL

SOURCES = $(SRC_DIR)/main_sim.c \
          $(DRIVERS_DIR)/sim_gpio.c \
          $(DRIVERS_DIR)/sim_time.c \
          $(HAL_DIR)/hal_gpio.c \
          $(HAL_DIR)/hal_time.c

OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = watering_system_sim.exe

# Rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean