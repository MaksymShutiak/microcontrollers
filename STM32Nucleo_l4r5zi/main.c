#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>

#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/uart.h"
#include "headers/registers.h"

static inline void spin(volatile uint32_t count) {
  while (count--) asm("nop");
}

int main(void) {
  RCC->CR |= (0x1UL << 8U);
  while ( !( RCC->CR & (0x1UL << 10U)) ) {};
  RCC->CFGR &= ~( 0x3UL << 0U );
  RCC->CFGR |=  ( 0x00000001UL );
  while ( ( RCC->CFGR & (0x3UL << 2U)) != 0x00000004UL) {};

  RCC->AHB2ENR = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 6); /* enable port A and port B and C */
  RCC->APB1ENR2 = (1 << 0); 
  RCC->APB2ENR = (1 << 14); 

  LPUART1->CR1 = (1 << 0) | (1 << 2) | (1 << 3);

  GPIOG->MODER  &= ~(3 << (7*2));
  GPIOG->MODER = (2 << 7 * 2);
  GPIOG->OTYPER &= ~(1 << 7);
  GPIOG->OSPEEDR  &= ~(3 << (7*2));
  GPIOG->OSPEEDR  |= (3 << (7*2));
  GPIOG->AFR[0] &= ~( ( 0xF << ( 7 * 4 ) ) );
  GPIOG->AFR[0] |= (8U << 7*4);

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

  LPUART1->BRR = 16000000 / 9600; // For 9600 baud rate (adjust according to your clock settings)
  LPUART1->CR1 = (1 << 0) | (1 << 2) | (1 << 3);


  for (;;) {
    while (!(LPUART1->ISR & (1 << 7))) {}
    LPUART1->TDR = 'j';

    GPIOB->BSRR |= (1 << 7);
    GPIOB->BSRR |= (1 << 14);
    GPIOC->BSRR |= (1 << 7);
    spin(9999999);
    GPIOB->BSRR |= (1 << (16 + 7));
    GPIOB->BSRR |= (1 << (16 + 14));
    GPIOC->BSRR |= (1 << (16 + 7));
    spin(9999999);
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
