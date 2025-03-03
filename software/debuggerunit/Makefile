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
MCU = cortex-m0plus
STACK_SIZE=0x8000
F_CPU=48000000
TARGET = $(BIN_DIR)/debugunit
LINKER_SCRIPT = samd11d14am-flash.ld

# Source Files
SRC_DIR = src

SOURCES = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

DEFINES += \
  -DDONT_USE_CMSIS_INIT \
  -DF_CPU=48000000 \
  -DSTACK_SIZE=$(STACK_SIZE)

# Flags
CFLAGS += -mcpu=$(MCU) $(DEFINES) -mthumb 
CFLAGS += -W -Wall --std=gnu11 -Os
CFLAGS += -fno-diagnostics-show-caret
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -funsigned-char -funsigned-bitfields
CFLAGS += -flto

LDFLAGS += -mcpu=$(MCU) -T $(LINKER_SCRIPT) --specs=nosys.specs --specs=nano.specs -e Reset_Handler
LDFLAGS += -Wl,--gc-sections -mthumb
LDFLAGS += -flto

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
