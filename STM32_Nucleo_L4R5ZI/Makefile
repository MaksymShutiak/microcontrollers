CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections \
            -I. -Iinclude -Icmsis_core/CMSIS/Core/Include -Icmsis_l4/Include \
            -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
LDFLAGS ?= -T link.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=./build/$@.map
SOURCES = main.c startup.c
# SOURCES += cmsis_l4/Source/Templates/gcc/startup_stm32l4r5xx.s # ST startup file. Compiler-dependent!

build: firmware.bin

firmware.elf: $(SOURCES) 
	rm -rf build
	mkdir build
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o ./build/$@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary ./build/$< ./build/$@

cmsis_core:
	git clone --depth 1 -b 5.9.0 https://github.com/ARM-software/CMSIS_5 $@

cmsis_l4:
	git clone --depth 1 -b v1.7.4 https://github.com/STMicroelectronics/cmsis_device_l4 $@

flash: 
	st-flash --reset write ./build/firmware.bin 0x8000000

clean:
	rm -rf ./build 
