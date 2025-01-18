# Directories
# TOOLCHAIN_ROOT = /usr
# TOOLCHAIN_BIN = $(TOOLCHAIN_ROOT)/bin
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Toolchain
# CC = $(TOOLCHAIN_BIN)/arm-none-eabi-gcc
# OBJCOPY = $(TOOLCHAIN_BIN)/arm-none-eabi-objcopy
# DEBUG = $(TOOLCHAIN_BIN)/arm-none-eabi-gdb
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
DEBUG = arm-none-eabi-gdb
RM = rm -rf

# MCU and Target Settings
MCU = cortex-m4
F_CPU = 48000000
STACK_SIZE=0x8000
TARGET = $(BIN_DIR)/kuben
LINKER_SCRIPT = same53j18a-flash.ld

# Source Files
SRC_DIR = src

SOURCES = $(shell find $(SRC_DIR) -type f -name "*.c" \
  ! -path "$(SRC_DIR)/CMSIS/*" \
  ! -path "$(SRC_DIR)/kuben.c" \
  ! -path "$(SRC_DIR)/drivers/*")
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Flags
CFLAGS = -mcpu=$(MCU) -DF_CPU=$(F_CPU) -DSTACK_SIZE=$(STACK_SIZE) -Wall -O2 -g 
LDFLAGS = -T $(LINKER_SCRIPT) -lm --specs=nano.specs -e Reset_Handler

# Build Rules
## Compiling Only
compile: $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

## Linking Only
link: $(TARGET).elf

$(TARGET).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

## Generate HEX
$(TARGET).hex: $(TARGET).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O ihex $< $@

# Phony Targets
.PHONY: all clean flash compile link

all: $(TARGET).hex

clean:
	$(RM) -r $(BUILD_DIR)

#flash: $(TARGET).hex
#	openocd -f interface/cmsis-dap.cfg -f target/atsam3x.cfg -c "program $< verify reset; exit"
