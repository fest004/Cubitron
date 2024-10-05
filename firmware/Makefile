# Makefile for compiling AVR projects

# MCU and clock frequency settings
MCU = atmega328p
F_CPU = 16000000UL

# Source and output files
SRC = src/
BIN = bin/
SOURCE = $(SRC)main.c         # Update this to your source file
OUTPUT_ELF = blinker.elf
OUTPUT_HEX = blinker.hex

# Compiler and tools
CC = clang
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
PROGRAMMER = usbasp         # Change to 'arduino' if using Arduino as a programmer
PORT = /dev/ttyACM0        # Change to your actual port if needed

# Flags
CFLAGS = -target avr -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Default target
all: $(OUTPUT_HEX)

# Compile the C file into an ELF binary
$(OUTPUT_ELF): $(SOURCE)
	$(CC) $(CFLAGS) -o $(BIN)$@ $<

# Generate the HEX file from the ELF binary
$(OUTPUT_HEX): $(BIN)$(OUTPUT_ELF)
	$(OBJCOPY) -O ihex $< $(BIN)$@

# Upload the HEX file to the Arduino
upload: $(OUTPUT_HEX)
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$<:i -P $(PORT)

# Clean up generated files
clean:
	rm -f $(OUTPUT_ELF) $(OUTPUT_HEX)

# Generate compile commands for tooling
compile_commands.json: $(SOURCE)
	@echo "[" > $@
	@echo "  {" >> $@
	@echo "    \"directory\": \"$(shell pwd)\"," >> $@
	@echo "    \"command\": \"$(CC) $(CFLAGS) -o $(OUTPUT_ELF) $(SOURCE)\"," >> $@
	@echo "    \"file\": \"$(SOURCE)\"" >> $@
	@echo "  }" >> $@
	@echo "]" >> $@

.PHONY: all clean upload compile_commands.json
