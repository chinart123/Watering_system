CC = gcc
CFLAGS = -I../Application/Inc -I../Drivers/Sim_Drivers
LDFLAGS = -lws2_32  # Thêm thư viện Windows nếu dùng Sleep()

SRC_DIR = ../Application/Src
SIM_SRC_DIR = ../Drivers/Sim_Drivers
SIM_DIR = Src

SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SIM_SRC_DIR)/*.c) \
       $(SIM_DIR)/main_sim.c

OBJS = $(addprefix Build/,$(notdir $(SRCS:.c=.o)))

TARGET = Build/watering_system_sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^  

Build/%.o: $(SRC_DIR)/%.c | Build
	$(CC) $(CFLAGS) -c $< -o $@  # DÙNG TAB

Build/%.o: $(SIM_SRC_DIR)/%.c | Build
	$(CC) $(CFLAGS) -c $< -o $@  # DÙNG TAB

Build/%.o: $(SIM_DIR)/%.c | Build
	$(CC) $(CFLAGS) -c $< -o $@  # DÙNG TAB

Build:
	mkdir -p Build

clean:
	rm -rf Build/*.o $(TARGET)

.PHONY: all clean