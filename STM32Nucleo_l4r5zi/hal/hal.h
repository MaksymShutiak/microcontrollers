#define GPIOEN(pin) (1 << pin)
#define GPIOAEN GPIOEN(0)
#define GPIOBEN GPIOEN(1)
#define GPIOCEN GPIOEN(2) 
#define GPIODEN GPIOEN(3)
#define GPIOEEN GPIOEN(4)
#define GPIOFEN GPIOEN(5)
#define GPIOGEN GPIOEN(6)
#define GPIOHEN GPIOEN(7)
#define GPIOIEN GPIOEN(8)
#define CLOCK_SPEED 4000000
#define BAUD_RATE 115200

#include "enums.h"
#include "helpers.h"
#include "gpio.h"
#include "systick.h"
#include "timer.h"
#include "uart.h"
