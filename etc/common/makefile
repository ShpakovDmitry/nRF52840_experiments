.PHONY := all clean
.DEFAULT_GOAL := all

ARCH := arm-none-eabi
MCU := cortex-m4

CC := $(ARCH)-gcc
AS := $(ARCH)-as
LD := $(ARCH)-ld
OBJDUMP := $(ARCH)-objdump
OBJCOPY := $(ARCH)-objcopy
OBJSIZE := $(ARCH)-size

SOURCE_DIR := ./
BUILD_DIR := build
OBJECT_DIR := $(BUILD_DIR)
DIRS := $(BUILD_DIR)

CC_SRC_FILES := $(wildcard $(SOURCE_DIR)/*.c)
CC_OBJ_FILES := $(CC_SRC_FILES:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)

CC_FLAGS := -c -Wall -Werror -mcpu=$(MCU) -mthumb -Os -std=c18
CC_FLAGS += -idirafter $(ROOTDIR)/include -fdata-sections -ffunction-sections
CC_FLAGS += -ffreestanding -nostdinc -idirafter $(ROOTDIR)/source
OBJDUMP_FLAGS := --disassemble-all -z
OBJCOPY_FLAGS := -O ihex 
OBJSIZE_FLAGS := 

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CC_FLAGS) $^ -o $@
	$(OBJSIZE) $(OBJSIZE_FLAGS) $@ > $(@:%.o=%.s)
	$(OBJDUMP) $(OBJDUMP_FLAGS) $@ >> $(@:%.o=%.s)

$(BUILD_DIR):
	mkdir --parents $(DIRS)

clean:
	rm -rf $(DIRS)

all: $(BUILD_DIR) $(CC_OBJ_FILES)
