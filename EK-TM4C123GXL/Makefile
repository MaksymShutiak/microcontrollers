CFLAGS ?= -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -fno-common
CFLAGS += -g3 -Os -ffunction-sections -fdata-sections -Wno-shadow
CFLAGS += -mcpu=cortex-m4
SOURCES = main.c

build: 
	mkdir build
	arm-none-eabi-gcc $(SOURCES) -c $(CFLAGS) -o ./build/main.o
	arm-none-eabi-gcc -T link.ld -nostdlib ./build/main.o -o ./build/firmware.elf

clean:
	rm -rf ./build 

