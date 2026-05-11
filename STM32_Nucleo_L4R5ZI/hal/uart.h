#define BUFFER_SIZE 32
#define LPUART1EN (1 << 0)

volatile char rx_buffer[BUFFER_SIZE];

typedef struct 
{
  volatile char* buffer;
  volatile int index;
  bool finished;
} uart_data;

uart_data ud = {
  buffer: rx_buffer,
  index: 0,
  finished: false,
};

static inline uint8_t uart_read_byte() {
  return (uint8_t) (LPUART1->RDR & 255);
}

static inline void uart_write_byte(uint8_t byte) {
  LPUART1->TDR = byte;
  while ((LPUART1->ISR & 1 << 7) == 0);
}

static inline void uart_write_buf(volatile char *buf, size_t len) {
  while (len-- > 0) uart_write_byte(*(uint8_t *) buf++);
}

static inline void set_uart_receive_buffer() 
{
    char received;
    bool uart_receive_started = (LPUART1->ISR & (1 << 5)) != 0;
    ud.finished = false;

    if (uart_receive_started) {
        received = uart_read_byte(); 
    }

    if (uart_receive_started && (ud.index < BUFFER_SIZE - 1)) {
        ud.buffer[ud.index++] = received;
    }

    ud.finished = uart_receive_started && (received == '\n' || received == '\r'); 

    if(ud.finished) {
        ud.buffer[ud.index] = '\0';
        ud.index = 0;
    }
}

void init_uart(USART_TypeDef * uart)
{
    int rx;
    int tx;
    GPIO_TypeDef * gpio;

    if (uart == LPUART1) {
      RCC->AHB2ENR |= GPIOGEN;
      RCC->APB1ENR2 |= LPUART1EN; 
      rx = 7;
      tx = 8;
      gpio = GPIOG;
    }
    gpio_set_mode(gpio, rx, GPIO_MODE_AF, 0);
    gpio_set_mode(gpio, tx, GPIO_MODE_AF, 1);
    gpio_set_af(gpio, rx);
    gpio_set_af(gpio, tx);
    uart->CR1 = 0;
    uart->BRR = (256*4000000)/115200;
    uart->CR1 = (1 << 3) | (1 << 2) | (1 << 0);
}
