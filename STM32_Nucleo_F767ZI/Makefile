CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
						-Wno-sign-conversion -Wno-error=sign-conversion \
            -g3 -Os -ffunction-sections -fdata-sections \
            -I. -Iinclude -I cmsis_core/CMSIS/Core/Include -I cmsis_f7/Include \
            -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
LDFLAGS ?= -T link.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=./build/$@.map
SOURCES = main.c startup.c

build: firmware.bin

firmware.elf: $(SOURCES) 
	rm -rf build
	mkdir build
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o ./build/$@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary ./build/$< ./build/$@

cmsis_core:
	git clone git@github.com:ARM-software/CMSIS_6.git $@

cmsis_f7:
	git clone git@github.com:STMicroelectronics/cmsis-device-f7.git $@

flash: 
	st-flash --reset write ./build/firmware.bin 0x8000000

clean:
	rm -rf ./build 
