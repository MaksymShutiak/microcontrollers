#include <stdint.h>
#include "hal.h"

int main(void) {
  set_gpio_mode(P0, BUILD_IN_BUTTON_1_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_1_PIN, GPIO_MODE_OUTPUT, 0);

  set_gpio_mode(P0, BUILD_IN_BUTTON_2_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_2_PIN, GPIO_MODE_OUTPUT, 0);

  set_gpio_mode(P0, BUILD_IN_BUTTON_3_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_3_PIN, GPIO_MODE_OUTPUT, 0);

  set_gpio_mode(P0, BUILD_IN_BUTTON_4_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_4_PIN, GPIO_MODE_OUTPUT, 0);

  while (1) {
    int button_1 = gpio_read(P0, BUILD_IN_BUTTON_1_PIN);
    int button_2 = gpio_read(P0, BUILD_IN_BUTTON_2_PIN);
    int button_3 = gpio_read(P0, BUILD_IN_BUTTON_3_PIN);
    int button_4 = gpio_read(P0, BUILD_IN_BUTTON_4_PIN);
    
    if (button_1) {
      gpio_write(P0, BUILD_IN_LED_1_PIN, HIGH);
    }
    else if (button_2) {
      gpio_write(P0, BUILD_IN_LED_2_PIN, HIGH);
    }
    else if (button_3) {
      gpio_write(P0, BUILD_IN_LED_3_PIN, HIGH);
    }
    else if (button_4) {
      gpio_write(P0, BUILD_IN_LED_4_PIN, HIGH);
    }
    else {
      gpio_write(P0, BUILD_IN_LED_4_PIN, LOW);
      gpio_write(P0, BUILD_IN_LED_3_PIN, LOW);
      gpio_write(P0, BUILD_IN_LED_2_PIN, LOW);
      gpio_write(P0, BUILD_IN_LED_1_PIN, LOW);
    }
  }
}

// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
  // memset .bss to zero, and copy .data section to RAM region
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

  main();             // Call main()
  for (;;) (void) 0;  // Infinite loop in the case if main() returns
}

extern void _estack(void);  // Defined in link.ld

// 16 standard and 91 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 42])(void) = {
    _estack, _reset};

