################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFM32GG11B/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: GG11_RTCDRV_UARTDRV_Test.axf

# Tool invocations
GG11_RTCDRV_UARTDRV_Test.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "GG11_RTCDRV_UARTDRV_Test.ld" -Xlinker --gc-sections -Xlinker -Map="GG11_RTCDRV_UARTDRV_Test.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o GG11_RTCDRV_UARTDRV_Test.axf "./CMSIS/EFM32GG11B/startup_efm32gg11b.o" "./CMSIS/EFM32GG11B/system_efm32gg11b.o" "./Drivers/dmadrv.o" "./Drivers/gpiointerrupt.o" "./Drivers/nvm.o" "./Drivers/nvm_hal.o" "./Drivers/rtcdriver.o" "./Drivers/sleep.o" "./Drivers/spidrv.o" "./Drivers/tempdrv.o" "./Drivers/uartdrv.o" "./Drivers/ustimer.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_dma.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_ldma.o" "./emlib/em_leuart.o" "./emlib/em_rtcc.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: GG11_RTCDRV_UARTDRV_Test.hex'
	arm-none-eabi-objcopy -O ihex "GG11_RTCDRV_UARTDRV_Test.axf" "GG11_RTCDRV_UARTDRV_Test.hex"
	@echo ' '

	@echo 'Building bin file: GG11_RTCDRV_UARTDRV_Test.bin'
	arm-none-eabi-objcopy -O binary "GG11_RTCDRV_UARTDRV_Test.axf" "GG11_RTCDRV_UARTDRV_Test.bin"
	@echo ' '

	@echo 'Building s37 file: GG11_RTCDRV_UARTDRV_Test.s37'
	arm-none-eabi-objcopy -O srec "GG11_RTCDRV_UARTDRV_Test.axf" "GG11_RTCDRV_UARTDRV_Test.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "GG11_RTCDRV_UARTDRV_Test.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) GG11_RTCDRV_UARTDRV_Test.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
