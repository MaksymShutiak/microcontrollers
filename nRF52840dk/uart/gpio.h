struct gpio {
  volatile uint32_t RESERVED[321], OUT, OUTSET, OUTCLR, IN, DIR, DIRSET, DIRCLR, LATCH, DETECTMODE, RESERVED_SECOND[118], PIN_CNF[32];
};
