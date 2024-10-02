CFLAGS ?= -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -fno-common
CFLAGS += -g3 -Os -ffunction-sections -fdata-sections -Wno-shadow
CFLAGS += -mcpu=cortex-m4
SOURCES = main.c

build: 
	mkdir build
	arm-none-eabi-gcc $(SOURCES) -c $(CFLAGS) -o ./build/main.o
	arm-none-eabi-gcc -T link.ld -nostdlib ./build/main.o -o ./build/firmware.elf
	arm-none-eabi-objcopy -O binary ./build/firmware.elf ./build/firmware.bin

flash: 
	st-flash --reset write ./build/firmware.bin 0x8000000

clean:
	rm -rf ./build 
