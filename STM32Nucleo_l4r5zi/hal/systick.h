static volatile uint64_t s_ticks;  // Milliseconds since boot
                                   //
void SysTick_Handler(void) {       // SyStick IRQ handler, triggered every 1ms
  s_ticks++;
}

struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define SYSTICK ((struct systick *) 0xE000E010)

static inline void systick_init(uint32_t ticks) {
  if ((ticks - 1) > 0xffffff) return;  // Systick timer is 24 bit
  SYSTICK->LOAD = ticks - 1;
  SYSTICK->VAL = 0;
  SYSTICK->CTRL = (1 << 0) | (1 << 1) | (1 << 2);  // Enable systick
}

