PROJECTNAME = tim1_interrupt
DEBUG = 1

# FOLDERS
SOURCE = src
INCLUDE = inc
BUILD = build

# FILES
SOURCES := $(shell find $(SOURCE) -type f -name *.c)
OBJECTS := $(SOURCES:$(SOURCE)/%.c=$(BUILD)/%.o)

# TOOLCHAIN
PREFIX = arm-none-eabi-
CC = gcc
SIZE = size
OBJCOPY = objcopy

# SETTINGS
CPU_flags = -mcpu=cortex-m3 -mthumb
OPT_flags = -O0
ifeq ($(DEBUG),1)
		DEBUG_flag = -ggdb3
 #endif
		LIB_file = STM32F103_HSE72_debug
else 
		DEBUG_flag = 
		LIB_file = STM32F103_HSE72_nodebug
endif
WARN_flags = -Wall -Wpedantic -Wextra
LANG_flags= -x assembler-with-cpp
FUNC_flags = -fdata-sections -ffunction-sections


# SUMMARY SETTINGS
C2O_flags = -c $(CPU_flags) $(OPT_flags) $(DEBUG_flag) $(FUNC_flags) -I$(INCLUDE) -specs=nano.specs
LINK_flags = -specs=nano.specs -T $(INCLUDE)/STM32F103XB_FLASH.ld -L$(INCLUDE) -lc -lm -lnosys -l$(LIB_file)  -Wl,-Map=$(BUILD)/$(PROJECTNAME).map,--cref -Wl,--gc-sections

# RULES
# Ulitmate goal is to have hex file
all: builddir $(BUILD)/$(PROJECTNAME).hex $(BUILD)/$(PROJECTNAME).bin
	@echo "DONE"
	
builddir: 
	@mkdir -p $(BUILD)

$(BUILD)/$(PROJECTNAME).hex: $(BUILD)/$(PROJECTNAME).elf
	@echo "Creating $@"
	@echo ----------------
	@$(PREFIX)$(OBJCOPY) -O ihex $^ $@

$(BUILD)/$(PROJECTNAME).bin: $(BUILD)/$(PROJECTNAME).elf
	@echo "Creating $@"
	@echo ----------------
	@$(PREFIX)$(OBJCOPY) -O binary $^ $@

$(BUILD)/$(PROJECTNAME).elf: $(OBJECTS)
	@echo "Building $@"
	@echo ----------------
	@$(PREFIX)$(CC) $(CPU_flags) $(LINK_flags) -o $@ $(OBJECTS)
	@echo "Size summary"
	@$(PREFIX)$(SIZE) $@ 
	@echo ----------------

$(BUILD)/%.o: $(SOURCE)/%.c
	@echo Compiling $@ from $^
	@echo ----------------
	@$(PREFIX)$(CC) $(C2O_flags) -o $@ $^
.PHONY: clean
clean:
	@echo "Cleaning $(BUILD)"
	@rm -rf $(BUILD)

