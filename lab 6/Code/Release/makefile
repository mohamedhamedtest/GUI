################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
lab4osc.lss \

FLASH_IMAGE += \
lab4osc.hex \

EEPROM_IMAGE += \
lab4osc.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lab4osc.elf secondary-outputs

# Tool invocations
lab4osc.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lab4osc.map -mmcu=atmega32 -o "lab4osc.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lab4osc.lss: lab4osc.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lab4osc.elf  >"lab4osc.lss"
	@echo 'Finished building: $@'
	@echo ' '

lab4osc.hex: lab4osc.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lab4osc.elf  "lab4osc.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab4osc.eep: lab4osc.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lab4osc.elf  "lab4osc.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lab4osc.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 lab4osc.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) lab4osc.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
