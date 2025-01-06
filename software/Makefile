# Directories
TOOLCHAIN_ROOT = /usr
TOOLCHAIN_BIN = $(TOOLCHAIN_ROOT)/bin
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Toolchain
CC = $(TOOLCHAIN_BIN)/arm-none-eabi-gcc
OBJCOPY = $(TOOLCHAIN_BIN)/arm-none-eabi-objcopy
DEBUG = $(TOOLCHAIN_BIN)/arm-none-eabi-gdb
RM = rm -rf

# MCU and Target Settings
MCU = cortex-m4
F_CPU = 48000000
TARGET = $(BIN_DIR)/kuben
LINKER_SCRIPT = ATSAME53J18A.ld

# Source Files
SRC = src
SOURCES = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Flags
CFLAGS = -mcpu=$(MCU) -mthumb -DF_CPU=$(F_CPU) -Wall -O2 -g 

LDFLAGS = -mcpu=$(MCU) -mthumb -T $(LINKER_SCRIPT) -lc -lm -lgcc --specs=nosys.specs -e Reset_Handler

# Build Rules
## Linking
$(TARGET).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

## Generate HEX
$(TARGET).hex: $(TARGET).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O ihex $< $@

## Compiling
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony Targets
.PHONY: all clean flash

all: $(TARGET).hex

clean:
	$(RM) $(BUILD_DIR)

#flash: $(TARGET).hex
#	openocd -f interface/cmsis-dap.cfg -f target/atsam3x.cfg -c "program $< verify reset; exit"
