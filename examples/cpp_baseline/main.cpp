extern "C" {
#include <core/system.h>
#include <esp8266.h>
#include <stdint.h>
}

#include "color.h"
#include "concepts.h"
#include "switch.h"
#include "led.h"
#include "validation.h"

void LightSetColor(LightConcept auto&& light, Color c) {
    light.set_color(c);
}

extern "C" void main() {
    constexpr gpio_num_t red_pin = GPIO_NUM_14;
    constexpr gpio_num_t green_pin = GPIO_NUM_12;
    constexpr gpio_num_t blue_pin = GPIO_NUM_13;
    constexpr gpio_num_t switch_pin = GPIO_NUM_5;

    validate_led_pins<red_pin, green_pin, blue_pin>();
    validate_switch_pin<switch_pin>();

    Led led(red_pin, green_pin, blue_pin);
    Switch sw(switch_pin);

    auto& light = led;

    LightSetColor(light, Color::OFF);
}

