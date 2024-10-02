# CFLAGS ?= -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -fno-common
CFLAGS += -g3 -Os -ffunction-sections -fdata-sections -Wno-shadow
# CFLAGS += -mmcu=avrxmega3
SOURCES = main.c

build: 
	mkdir build
	avr-gcc $(CFLAGS) -Os -o ./build/main.elf $(SOURCES)
	avr-objcopy -O ihex ./build/main.elf ./build/program.hex


flash: 
	avrdude -v -p t1627 -c pkobn_updi -U flash:w:./build/program.hex:i

clean:
	rm -rf ./build 
