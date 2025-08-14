CC = gcc
CFLAGS = -I../Application/Inc -I../Drivers/Sim_Drivers
SRC_DIR = ../Application/Src
SIM_SRC_DIR = ../Drivers/Sim_Drivers
SIM_DIR = Src

SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SIM_SRC_DIR)/*.c) \
       $(SIM_DIR)/main_sim.c

OBJS = $(patsubst %.c,Build/%.o,$(notdir $(SRCS)))

TARGET = Build/watering_system_sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

Build/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

Build/%.o: $(SIM_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

Build/%.o: $(SIM_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Build/*.o $(TARGET)