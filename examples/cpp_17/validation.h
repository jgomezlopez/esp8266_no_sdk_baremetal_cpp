#pragma once

extern "C" {
#include <esp8266.h>
}

template<gpio_num_t Pin>
void validate_switch_pin() {
    static_assert(Pin >= GPIO_NUM_0 && Pin < GPIO_MAX && Pin != GPIO_NUM_16,
                  "Invalid GPIO pin for Switch (compile-time)");
}

template<gpio_num_t R, gpio_num_t G, gpio_num_t B>
void validate_led_pins() {
    static_assert(R >= GPIO_NUM_0 && R < GPIO_MAX && R != GPIO_NUM_16, "Invalid R pin");
    static_assert(G >= GPIO_NUM_0 && G < GPIO_MAX && G != GPIO_NUM_16, "Invalid G pin");
    static_assert(B >= GPIO_NUM_0 && B < GPIO_MAX && B != GPIO_NUM_16, "Invalid B pin");
    static_assert(R != G && R != B && B != G, "Duplicated pin");
}

template<uint32_t Speed>
void validate_uart_speed() {
    static_assert(Speed >= 1200 && Speed <= 921600,
                  "Invalid UART speed (compile-time)");
}

