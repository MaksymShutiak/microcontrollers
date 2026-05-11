// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
  // memset .bss to zero, and copy .data section to RAM region
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;
  extern void main(void);
  main();             // Call main()
  for (;;) (void) 0;  // Infinite loop in the case if main() returns
}

extern void SysTick_Handler(void);  // Defined in main.c
extern void _estack(void);  // Defined in link.ld
                            //
// 16 standard and 95 STM32-specific handlers
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
__attribute__((section(".vectors"))) void (*tab[16 + 95])(void) = {
    _estack, 
    _reset, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0,
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    SysTick_Handler,
};
