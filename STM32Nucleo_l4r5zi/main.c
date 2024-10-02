#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>

#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/uart.h"
#include "headers/registers.h"

#define FREQ 80000000  // CPU frequency, 16 Mhz
#define BAUD_RATE 9600  // CPU frequency, 16 Mhz
#define BIT(x) (1UL << (x))

#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) (pin >> 8)
#define GPIO(bank) ((struct gpio *) (0x48000000 + 0x400 * (bank)))

/* static inline void gpio_write(uint16_t pin, bool val) { */
/*   struct gpio *gpio = GPIO(PINBANK(pin)); */
/*   gpio->BSRR = (1U << PINNO(pin)) << (val ? 0 : 16); */
/* } */
static inline void spin(volatile uint32_t count) {
  while (count--) asm("nop");
}

static inline void gpio_set_af(uint16_t pin, uint8_t af_num) {
  struct gpio *gpio = GPIO(PINBANK(pin));  // GPIO bank
  int n = PINNO(pin);                      // Pin number
  gpio->AFR[n >> 3] &= ~(15UL << ((n & 7) * 4));
  gpio->AFR[n >> 3] |= ((uint32_t) af_num) << ((n & 7) * 4);
}

static inline void uart_write_byte(struct uart *uart, uint8_t byte) {
  uart->TDR = byte;
  while ((uart->ISR & BIT(7)) == 0) spin(1);
}

static inline void uart_write_buf(struct uart *uart, char *buf, size_t len) {
  while (len-- > 0) uart_write_byte(uart, *(uint8_t *) buf++);
}


int main(void) {
  RCC->APB1ENR1 = (1 << 17); 
  RCC->AHB2ENR = (1 << 0) | (1 << 1) | (1 << 2); /* enable port A and port B and C */
  UART2->CR1 = 0;                           // Disable this UART
  UART2->BRR = FREQ / BAUD_RATE;                 // FREQ is a UART bus frequency
  UART2->CR1 |= (1 << 0) | (1 << 2) | (1 << 3);

  GPIOA->MODER  &= ~(3 << (2*2));
  GPIOA->MODER = (2 << 2 * 2);
  gpio_set_af(PIN('A', 2), 7);

  GPIOC->MODER  &= ~(3 << (7*2));
  GPIOC->MODER  |= (1 << (7*2));
  GPIOC->OTYPER &= ~(1 << 7);
  /**/
  GPIOB->MODER  &= ~(3 << (14*2));
  GPIOB->MODER |= (1 << 14 * 2);
  GPIOB->OTYPER &= ~(1 << 14);

  GPIOB->MODER  &= ~(3 << (7*2));
  GPIOB->MODER |= (1 << (7*2));
  GPIOB->OTYPER &= ~(1 << 7);


  for (;;) {
    uart_write_buf(UART2, "hi\r\n", 4);
    GPIOB->BSRR |= (1 << 7);
    GPIOB->BSRR |= (1 << 14);
    GPIOC->BSRR |= (1 << 7);
    spin(99999);
    GPIOB->BSRR |= (1 << (16 + 7));
    GPIOB->BSRR |= (1 << (16 + 14));
    GPIOC->BSRR |= (1 << (16 + 7));
    spin(99999);
  }
  return 0;
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
__attribute__((section(".vectors"))) void (*const tab[16 + 95])(void) = {
    _estack, _reset};
