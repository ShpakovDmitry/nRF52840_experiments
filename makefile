.PHONY := all clean flash submake link
.DEFAULT_GOAL := all

TARGET := firmware
ARCH := arm-none-eabi
MCU := cortex-m4

CC := $(ARCH)-gcc
AS := $(ARCH)-as
LD := $(ARCH)-ld
OBJDUMP := $(ARCH)-objdump
OBJCOPY := $(ARCH)-objcopy
OBJSIZE := $(ARCH)-size

SOURCE_DIR := source
BUILD_DIR := build
LD_SCRIPT_DIR := etc/linker
DIRS := $(BUILD_DIR)

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

LD_SCRIPT_FILE := $(LD_SCRIPT_DIR)/nrf52840.ld
LD_FLAGS := -T $(LD_SCRIPT_FILE) -Map $(BUILD_DIR)/$(TARGET).map --gc-sections
LD_FLAGS += -nostartfiles -nolibc -nostdlib -nodefaultfiles
OBJDUMP_FLAGS := --disassemble-all -z
OBJCOPY_FLAGS := -O ihex 
OBJSIZE_FLAGS := 


link:
	$(eval  CC_OBJ_FILES := $(call rwildcard,$(SOURCE_DIR),*.o))
	$(LD) $(LD_FLAGS) $(CC_OBJ_FILES) -o $(BUILD_DIR)/$(TARGET).elf
	$(OBJSIZE) $(OBJSIZE_FLAGS) $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).s
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(BUILD_DIR)/$(TARGET).elf >> $(BUILD_DIR)/$(TARGET).s
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	$(OBJSIZE) $(OBJSIZE_FLAGS) $(BUILD_DIR)/$(TARGET).elf

CURRDIR := $(PWD)

$(BUILD_DIR):
	mkdir --parents $(DIRS)

clean:
	rm -rf $(DIRS)
	make -C ./source/application clean ROOTDIR=$(CURRDIR)
	make -C ./source/application/scheduler clean ROOTDIR=$(CURRDIR)
	make -C ./source/ringbuffer clean ROOTDIR=$(CURRDIR)
	make -C ./source/runtime clean ROOTDIR=$(CURRDIR)
	make -C ./source/stdlib clean ROOTDIR=$(CURRDIR)
	make -C ./source/target/nrf52840 clean ROOTDIR=$(CURRDIR)

all: submake $(BUILD_DIR) link

submake: 
	make -C ./source/application ROOTDIR=$(CURRDIR)
	make -C ./source/application/scheduler ROOTDIR=$(CURRDIR)
	make -C ./source/ringbuffer ROOTDIR=$(CURRDIR)
	make -C ./source/runtime ROOTDIR=$(CURRDIR)
	make -C ./source/stdlib ROOTDIR=$(CURRDIR)
	make -C ./source/target/nrf52840 ROOTDIR=$(CURRDIR)

flash: all
	nrfjprog -f nrf52 --program build/firmware.hex --sectorerase
	nrfjprog -f nrf52 --pinreset
