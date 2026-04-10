TARGET := $(shell pwd)
TARGET := $(shell basename $(TARGET))

# debug build
DEBUG = 1
# optimization
OPT = -Og

BUILD_DIR = build

C_SOURCES = \
Code/src/main.c \
CMSIS/src/core_cm3.c \
CMSIS/src/system_stm32f10x.c

ASM_SOURCES = \
startup_stm32f103x6.s

PREFIX = arm-none-eabi-

ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
CPU = -mcpu=cortex-m3

MCU = $(CPU) -mthumb

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS = \
-DUSE_CMSIS_DRIVER \
-DSTM32F103xx

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES = \
-ICode \
-ICode/inc \
-ICode/src \
-ICMSIS \
-ICMSIS/inc \
-ICMSIS/src

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# link script
LDSCRIPT = STM32F103C6Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# build
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

clean:
	-rm -fR $(BUILD_DIR)

# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)

PROJECT_NAME = $(TARGET)
NRST_USE = $(HARDWARE_RESET_USE)
prog: $(BUILD_DIR)/$(TARGET).elf
	PROJECT_NAME='$(PROJECT_NAME)' TARGET_CFG='target/stm32f1x.cfg' interface/./build_and_firmware_script

read: $(BUILD_DIR)/read_flash.bin
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg  -f interface/reset.cfg -c init -c "reset halt" -c "flash read_bank 0 firmwareF1.bin 0 0x8000" -c reset -c exit