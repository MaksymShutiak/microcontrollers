#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 3250000UL
#define BAUD_RATE 9600UL
#include <util/delay.h>
/* #include "iotn1627.h" */
#define PORTA ((struct PORT *) 0x0400)
#define PORTB ((struct PORT *) 0x0420)
#define PORTC ((struct PORT *) 0x0440)
#define USART0 (*(USART_t *) 0x0800)
#define CLKCTLR (*(CLK_t *) 0x0060) 

typedef struct CLK_stuct {
    volatile uint8_t CTRLA, CTRLB, LOCK, STATUS, RESERVED[11], MCTRLA, MCALIBA, MCALIBB, RESERVED1[4],
                     KCTRLA, RESERVED2[2], XCTRLA;
} CLK_t;

struct PORT {
    volatile uint8_t DIR, DIRSET, DIRCLR, DIRTGL, OUT, OUTSET, 
                     OUTCLR, OUTTGL, IN, INTFLAGS, PORTCTRL, RESERVED[5], 
                     PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7;
};

typedef struct USART_struct {
   volatile uint8_t RXDATAL;
   volatile uint8_t RXDATAH;
   volatile uint8_t TXDATAL; 
   volatile uint8_t TXDATAH; 
   volatile uint8_t STATUS;
   volatile uint8_t CTRLA;
   volatile uint8_t CTRLB; 
   volatile uint8_t CTRLC; 
   volatile uint16_t BAUD; 
   /* volatile uint8_t BAUDL;  */
   volatile uint8_t RESERVER0; 
   volatile uint8_t CTRLD;
   volatile uint8_t DBGCTRL; 
   volatile uint8_t EVCTRL; 
   volatile uint8_t TXPLCTRL; 
   volatile uint8_t RXPLCTRL;
} USART_t;


int main() {
    USART0.CTRLB = (1 << 6) | (1 << 4); // Enable receiver and transmitter
     
    USART0.BAUD = (uint16_t)((64*F_CPU)/(16*BAUD_RATE)); /* 64*3250000/(16*115200) */
    USART0.STATUS |= (1 << 6);

    PORTB->DIRSET |= (1 << 7);
    PORTB->DIRSET |= (1 << 5);
    PORTB->DIRSET |= (1 << 2);
    PORTC->PIN4 |= (1 << 3);

    while (1) {
      PORTB->OUTTGL = (1 << 5) | (1 << 7);

      USART0.TXDATAL = 'q';
      while(!((USART0.STATUS) & 0x20));
      USART0.STATUS |= (1 << 6);

      USART0.TXDATAL = ((~(PORTC->IN) & (1<<4)) == 0) ? '0': '1';
      while(!((USART0.STATUS) & 0x20));
      USART0.STATUS |= (1 << 6);

      USART0.TXDATAL = '\n';
      while(!((USART0.STATUS) & 0x20));
      USART0.STATUS |= (1 << 6);

      _delay_ms(1000);
    }
}

