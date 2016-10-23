################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/PubSubClient/src/subdir.mk
-include libraries/ESP8266WiFi/src/subdir.mk
-include libraries/DHT_sensor_library/subdir.mk
-include core/core/umm_malloc/subdir.mk
-include core/core/spiffs/subdir.mk
-include core/core/libb64/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/arduino.ar \

ELF += \
controlStatus.elf \

HEX += \
controlStatus.hex \


# All Target
all: controlStatus

# Tool invocations
controlStatus: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/tools/esp8266/xtensa-lx106-elf-gcc/1.20.0-26-gb404fb9-2/bin/xtensa-lx106-elf-size" -A "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/controlStatus.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/tools/esp8266/xtensa-lx106-elf-gcc/1.20.0-26-gb404fb9-2/bin/xtensa-lx106-elf-ar" cru  "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/arduino.ar"    /media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

controlStatus.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/tools/esp8266/xtensa-lx106-elf-gcc/1.20.0-26-gb404fb9-2/bin/xtensa-lx106-elf-gcc" -g -w -Os -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static "-L/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/lib" "-L/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/ld" "-Teagle.flash.4m1m.ld" -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,register_chipv6_phy  -o "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/controlStatus.elf" -Wl,--start-group   $(LINK_OBJ) $(AR)  "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/arduino.ar" -lm -lgcc -lhal -lphy -lpp -lnet80211 -lwpa -lcrypto -lmain -lwps -laxtls -lsmartconfig -lmesh -lwpa2 -llwip_gcc -lstdc++ -Wl,--end-group  "-L/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release"
	@echo 'Finished building: $@'
	@echo ' '

controlStatus.hex: $(ELF)
	@echo 'Create eeprom image'
	"/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/tools/esp8266/esptool/0.4.9/esptool" -eo "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/sloeber/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/bootloaders/eboot/eboot.elf" -bo "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/controlStatus.bin" -bm dio -bf 40 -bz 4M -bs .text -bp 4096 -ec -eo "/media/hugh/50945f07-d0f4-497e-9ee1-3cde40a92bcb/work4/controlStatus/Release/controlStatus.elf" -bs .irom0.text -bs .text -bs .data -bs .rodata -bc -ec
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
