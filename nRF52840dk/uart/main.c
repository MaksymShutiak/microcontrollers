#include <stdint.h>
#include "hal.h"

#define UART_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define UART_BAUDRATE_BAUDRATE_Baud115200 () /*!< 115200 baud. */
#define UART_BAUDRATE_BAUDRATE_Pos (0UL) /*!< Position of BAUDRATE field. */
#define UART_CONFIG_PARITY_Pos (1UL) /*!< Position of PARITY field. */
#define UART_CONFIG_PARITY_Included (7UL) /*!< Parity bit included. */
#define UART_CONFIG_HWFC_Disabled (0UL) /*!< Hardware flow control disabled. */
#define UART_CONFIG_HWFC_Pos (0UL) /*!< Position of HWFC field. */

#define PIN_TXD 6
#define PIN_RXD 8

int main(void) {
  uint8_t hello_world[] = "Ma";
  CLOCK->TASKS_HFCLKSTART = 1;
  while (CLOCK->EVENTS_HFCLKSTARTED == 0);
  CLOCK->EVENTS_HFCLKSTARTED = 0;

  // Configure the UARTE with no flow control, one parity bit and 115200 baud rate
  UARTE0->CONFIG = (UART_CONFIG_HWFC_Disabled   << UART_CONFIG_HWFC_Pos) |
                       (UART_CONFIG_PARITY_Included << UART_CONFIG_PARITY_Pos); 
  
  UARTE0->BAUDRATE = 0x01D60000;
  
  // Select TX and RX pins
  UARTE0->PSEL_TXD = 0x7fffffc6;
  
  // Enable the UART (starts using the TX/RX pins)
  UARTE0->ENABLE = 0x00000008;
  
  // Configure transmit buffer and start the transfer

  set_gpio_mode(P0, BUILD_IN_BUTTON_1_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_1_PIN, GPIO_MODE_OUTPUT, 0);

  set_gpio_mode(P0, BUILD_IN_BUTTON_2_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_2_PIN, GPIO_MODE_OUTPUT, 0);

  set_gpio_mode(P0, BUILD_IN_BUTTON_3_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_3_PIN, GPIO_MODE_OUTPUT, 0);

  set_gpio_mode(P0, BUILD_IN_BUTTON_4_PIN, GPIO_MODE_INPUT, 3);
  set_gpio_mode(P0, BUILD_IN_LED_4_PIN, GPIO_MODE_OUTPUT, 0);

    while (1) {
    gpio_write(P0, BUILD_IN_LED_1_PIN, HIGH);
    spin(9999999);
    UARTE0->TXD_MAXCNT = sizeof(hello_world);
    UARTE0->TXD_PTR = (uint32_t)&hello_world;
    UARTE0->TASKS_STARTTX = 1;
    // while (UARTE0->EVENTS_ENDTX == 0){}
    // UARTE0->TASKS_STARTTX = 1;
    // UARTE0->TASKS_STOPTX = 1;
    // while (UARTE0->EVENTS_TXSTOPPED == 0);
  

    gpio_write(P0, BUILD_IN_LED_1_PIN, LOW);
    spin(9999999);


    // gpio_write(P0, BUILD_IN_LED_2_PIN, HIGH);
    // gpio_write(P0, BUILD_IN_LED_3_PIN, HIGH);
    // gpio_write(P0, BUILD_IN_LED_4_PIN, HIGH);
    // spin(9999999);
    // gpio_write(P0, BUILD_IN_LED_4_PIN, LOW);
    // gpio_write(P0, BUILD_IN_LED_3_PIN, LOW);
    // gpio_write(P0, BUILD_IN_LED_2_PIN, LOW);
    // gpio_write(P0, BUILD_IN_LED_1_PIN, LOW);
    // spin(9999999);


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

