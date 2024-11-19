void gpio_set_mode(GPIO_TypeDef* gpio, int pin, int mode, int speed) {
    gpio->MODER  &= ~(3UL << (pin * 2)); /* reset before set */
    gpio->MODER |= ((unsigned) mode << pin * 2); 
    if (speed == 1) {
       gpio->OTYPER &= ~(1UL << pin); 
    }
}

void gpio_write(GPIO_TypeDef* gpio, int pin, bool status) {
    if (status)
    {
        gpio->BSRR |= (1UL << pin);
    } else {
        gpio->BSRR |= (1UL << (pin + 16));
    }
}

void gpio_set_af(GPIO_TypeDef* gpio, int pin) {
  if (pin < 8) {
    gpio->AFR[0] &= ~(0UL);
    gpio->AFR[0] |= (8UL << (pin * 4));
  } else {
    gpio->AFR[1] &= ~(0UL);
    gpio->AFR[1] |= (8UL << ((pin * 4) - 32));
  }
}
