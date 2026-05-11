#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f767xx.h"
#include "hal/hal.h"

int main(void) {
  RCC->APB2ENR |= (1 << 14); // Enable SYSCFG
  RCC->AHB1ENR |= GPIOAEN | GPIOBEN | GPIOCEN | GPIODEN |  GPIOGEN; /* enable port A and port B and C */

  init_uart(USART3);
  uint32_t timer;
  uint32_t period = 1000;
  systick_init(CLOCK_SPEED / period);

  gpio_set_mode(GPIOB, 7, GPIO_MODE_OUTPUT, 1);
  gpio_set_mode(GPIOB, 0, GPIO_MODE_OUTPUT, 1);
  gpio_set_mode(GPIOB, 14, GPIO_MODE_OUTPUT, 1);
  gpio_set_mode(GPIOC, 7, GPIO_MODE_OUTPUT, 1);

  for (;;) {
    gpio_write(GPIOB, 0, true);
    gpio_write(GPIOB, 14, true);
    set_uart_receive_buffer();

    if(ud.finished && my_strcmp(ud.buffer, "led_b_0_on\0")) {
      gpio_write(GPIOB, 0, true);
      uart_write_buf(rx_buffer, sizeof(rx_buffer));
      uart_write_byte('\n');
    }

    if(ud.finished && my_strcmp(ud.buffer, "led_b_0_off\0")) {
      gpio_write(GPIOB, 0, false);
      uart_write_buf(rx_buffer, sizeof(rx_buffer));
      uart_write_byte('\n');
    }

    char val = (~(GPIOB->IDR) & (1 << 7)) ? '1' : '0';

    if (timer_expired(&timer, period, (unsigned)s_ticks)) {
      static bool c7;
      gpio_write(GPIOB, 7, c7);
      uart_write_buf(&val, 1);
      uart_write_buf("\n", 1);
      c7 = !c7;
    }
  }
  return 0;
}
