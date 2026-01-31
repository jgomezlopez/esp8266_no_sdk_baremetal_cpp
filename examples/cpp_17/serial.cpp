#include "serial.h"

Serial::Serial(const uint32_t speed) {
    uart_init(0, speed, WORD_8_BITS, STOP_1_BIT);
}

void Serial::set_color(Color::Name c) {
    switch (c) {
        case Color::OFF:    uart_printf("OFF\r\n");    break;
        case Color::RED:    uart_printf("RED\r\n");    break;
        case Color::GREEN:  uart_printf("GREEN\r\n");  break;
        case Color::BLUE:   uart_printf("BLUE\r\n");   break;
        case Color::YELLOW: uart_printf("YELLOW\r\n"); break;
        case Color::PURPLE: uart_printf("PURPLE\r\n"); break;
        case Color::CYAN:   uart_printf("CYAN\r\n");   break;
        case Color::WHITE:  uart_printf("WHITE\r\n");  break;
    }
}

