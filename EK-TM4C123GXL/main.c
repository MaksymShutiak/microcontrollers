#include <inttypes.h>
#include <stdbool.h>

/* #define RCC ((struct rcc *) 0x40021000) */
#define SYSCTL_RCGCGPIO_R (*((volatile uint32_t *) 0x400FE608))
#define SYSCTL_PRGPIO_R       (*((volatile uint32_t *)0x400FEA08))   // GPIO Peripheral Ready
#define GPIOF ((struct gpio *) 0x40025000)
#define SYSCTL_RCGCGPIO_PORTF (1 << 5)  // Clock gating control for Port F
/* #define GPIO_PORTF_DIR_R      (*((volatile uint32_t *)0x40025400))   // GPIO Direction */
/* #define GPIO_PORTF_DEN_R      (*((volatile uint32_t *)0x4002551C))   // GPIO Digital Enable */
/* #define GPIO_PORTF_DATA_R     (*((volatile uint32_t *)0x400253FC))   */
#define GPIO_PIN_1            (1 << 1)
#define GPIO_PIN_2            (1 << 2)
#define GPIO_PIN_3            (1 << 3)

static inline void spin(volatile uint32_t count) {
  while (count--) asm("nop");
}


struct gpio {
    volatile uint32_t RESERED1[255], DATA, DIR, IS, IBE, IEV, IM,
                      RIS, MIS, ICR, AFSEL, RESERED2[55], DR2R,
                      DR4R, DR8R, ODR, PUR, PDR, SLR, DEN, 
                      LOCK, CR, AMSEL, PCTL, ADCCTL, DMACTL,
                      RESERED3[691], PeriphID4, PeriphID5, PeriphID6, PeriphID7, 
                      PeriphID0, PeriphID1, PeriphID2, PeriphID3, PCellID0,
                      PCellID1, PCellID2, PCellID3;
};

void delay(int count) {
    volatile int i;
    for (i = 0; i < count; i++);
}

int main(void) {
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_PORTF;
  /* while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_PORTF) == 0) { */
  /*     // Wait for the peripheral to be ready */
  /* } */
  GPIOF->DIR  |= GPIO_PIN_1;
  GPIOF->DIR  |= GPIO_PIN_2;
  GPIOF->DIR  |= GPIO_PIN_3;
  GPIOF->DEN |= GPIO_PIN_1;
  GPIOF->DEN |= GPIO_PIN_2;
  GPIOF->DEN |= GPIO_PIN_3;
  GPIOF->DATA |= GPIO_PIN_1;
  GPIOF->DATA |= GPIO_PIN_2;
  /* Step 2: Set PF1 (Red LED) as output */
  /* GPIO_PORTF_DIR_R |= GPIO_PIN_1;    // Set PF1 as output */

  /* Step 3: Enable the digital function of PF1 */
  /* GPIO_PORTF_DEN_R |= GPIO_PIN_1;    // Enable PF1 as digital pin */

  /* Step 4: Turn on the Red LED (set PF1 high) */
  /* GPIO_PORTF_DATA_R |= GPIO_PIN_1;   // Set PF1 to high (turn on Red LED) */

  while(1) {
    GPIOF->DATA ^= (1 << 3);

    delay(1000000);
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
__attribute__((section(".vectors"))) void (*const tab[16 + 155])(void) = {
    _estack, _reset};

