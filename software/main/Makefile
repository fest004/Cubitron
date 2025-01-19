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
STACK_SIZE=0x8000
TARGET = $(BIN_DIR)/kuben
LINKER_SCRIPT = same53j18a-flash.ld

# Source Files
SRC_DIR = src

SOURCES = $(shell find $(SRC_DIR) -type f -name "*.c" \
  ! -path "$(SRC_DIR)/kuben.c" \
  ! -path "$(SRC_DIR)/drivers-external/*"\
  ! -path "$(SRC_DIR)/platform/drivers/*"\
  ! -path "$(SRC_DIR)/RTOS2/*")
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Flags
CFLAGS = -mcpu=$(MCU) -DSTACK_SIZE=$(STACK_SIZE) -DUSE_CMSIS_INIT -Wall -O2 -g 
LDFLAGS = -T $(LINKER_SCRIPT) -lm --specs=nano.specs -e Reset_Handler

# Build Rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

## Generate HEX
$(TARGET).hex: $(TARGET).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O ihex $< $@

# Phony Targets
.PHONY: all clean flash compile link

link: $(TARGET).elf

compile: $(OBJECTS)

all: $(TARGET).hex

clean:
	$(RM) -r $(BUILD_DIR)

#flash: $(TARGET).hex
#	openocd -f interface/cmsis-dap.cfg -f target/atsam3x.cfg -c "program $< verify reset; exit"
