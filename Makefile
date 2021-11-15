.PHONY := all clean flash submake link
.DEFAULT_GOAL := all

TARGET := firmware
MCU := nRF52840
ARCH := cortex-m4
TOOLCHAIN_ARCH := arm-none-eabi

CC := $(TOOLCHAIN_ARCH)-gcc
AS := $(TOOLCHAIN_ARCH)-as
LD := $(TOOLCHAIN_ARCH)-ld
OBJDUMP := $(TOOLCHAIN_ARCH)-objdump
OBJCOPY := $(TOOLCHAIN_ARCH)-objcopy
OBJSIZE := $(TOOLCHAIN_ARCH)-size

SOURCE_DIR := ./source
BUILD_DIR := ./build
LIBS_DIR := $(SOURCE_DIR)/libs
INC_DIRS := $(shell find $(SOURCE_DIR) -type d)

SRC_FILES := $(shell find $(SOURCE_DIR) -name '*.cpp' -or -name '*.c' -or -name '*.S')
OBJ_FILES := $(SRC_FILES:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJ_FILES:.o=.d)
LD_SCRIPT_FILE := $(SOURCE_DIR)/application/arch/$(MCU)/linker/nRF52840.ld

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP
AS_FLAGS :=
CC_FLAGS := -Wall -Werror -mcpu=$(ARCH) -mthumb -Os -std=c18
CC_FLAGS += -fdata-sections -ffunction-sections -ffreestanding -nostdinc
CXX_FLAGS := -Wall -Werror -mcpu=$(ARCH) -mthumb -Os -std=c++17
CXX_FLAGS += -fdata-sections -ffunction-sections 
CXX_FLAGS += -fms-extensions -fno-exceptions -fno-rtti -fno-use-cxa-atexit
CXX_FLAGS += -fno-threadsafe-statics -fstrict-volatile-bitfields
CXX_FLAGS += -Wextra -Wcast-align -Wconversion -Wsign-conversion -Wold-style-cast
CXX_FLAGS += -Wshadow -Wlogical-op -Wsuggest-override -Wsuggest-final-types
CXX_FLAGS += -Wsuggest-final-methods -pedantic
LD_FLAGS := -T $(LD_SCRIPT_FILE) -Map $(BUILD_DIR)/$(TARGET).map --gc-sections
LD_FLAGS += --nostdlib
OBJDUMP_FLAGS := --disassemble-all -z
OBJCOPY_FLAGS := -O ihex 
OBJSIZE_FLAGS := 



all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/$(TARGET).hex: $(OBJ_FILES)
	$(LD) $(LD_FLAGS) $(OBJ_FILES) -o $(@:.hex=.elf)
	$(OBJSIZE) $(OBJSIZE_FLAGS) $(@:.hex=.elf) > $(@:.hex=.S)
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(@:.hex=.elf) >> $(@:.hex=.S)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(@:.hex=.elf) $@
	$(OBJSIZE) $(OBJSIZE_FLAGS) $(@:.hex=.elf)

$(BUILD_DIR):
	mkdir --parents $@

$(BUILD_DIR)/%.S.o: %.S
	mkdir --parents $(dir $@)
	$(AS) $(AS_FLAGS) $< -o $@
	$(OBJSIZE) $(OBJSIZE_FLAGS) $@ > $@.S
	$(OBJDUMP) $(OBJDUMP_FLAGS) $@ >> $@.S

$(BUILD_DIR)/%.c.o: %.c
	mkdir --parents $(dir $@)
	$(CC) $(CPPFLAGS) $(CC_FLAGS) -c $< -o $@
	$(OBJSIZE) $(OBJSIZE_FLAGS) $@ > $@.S
	$(OBJDUMP) $(OBJDUMP_FLAGS) $@ >> $@.S

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir --parents $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c $< -o $@
	$(OBJSIZE) $(OBJSIZE_FLAGS) $@ > $@.S
	$(OBJDUMP) $(OBJDUMP_FLAGS) $@ >> $@.S

clean:
	rm -rf $(BUILD_DIR)

flash:
	nrfjprog -f nrf52 --program $(BUILD_DIR)/$(TARGET).hex --sectorerase
	nrfjprog -f nrf52 --pinreset
