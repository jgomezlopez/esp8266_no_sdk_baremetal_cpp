#include "serial.h"

Serial::Serial(const uint32_t speed) {
    uart_init(0, speed, WORD_8_BITS, STOP_1_BIT);
}

void Serial::set_color(Color c) {
    using enum Color;
    switch (c) {
        case OFF:    uart_printf("OFF\r\n");    break;
        case RED:    uart_printf("RED\r\n");    break;
        case GREEN:  uart_printf("GREEN\r\n");  break;
        case BLUE:   uart_printf("BLUE\r\n");   break;
        case YELLOW: uart_printf("YELLOW\r\n"); break;
        case PURPLE: uart_printf("PURPLE\r\n"); break;
        case CYAN:   uart_printf("CYAN\r\n");   break;
        case WHITE:  uart_printf("WHITE\r\n");  break;
    }
}

