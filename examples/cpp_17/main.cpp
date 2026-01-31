extern "C" {
#include <core/system.h>
#include <esp8266.h>
#include <stdint.h>
}

#include "color.h"
#include "switch.h"
#include "led.h"
#include "serial.h"
#include "validation.h"
#include "cpp_timer.h"

// -----------------------------------------------------------------------------
// Free functions
bool SwitchPushed(Trigger& sw) {
    return sw.switch_pushed();
}

void LightSetColor(Light& light, Color::Name c) {
    light.set_color(c);
}

void set_color_for_ms (Light& self, Color::Name c, Timer& timer, uint32_t ms) {
    self.set_color(c);
    timer.delay(ms);
    self.set_color(Color::OFF);
}

bool has_been_pushed(Trigger& self, Timer& timer, uint32_t timeout_ms) {
    uint32_t start = timer.now();
    bool pressed = false;
    while ((timer.now() - start) < timeout_ms) {
        if (SwitchPushed(self)) {
            pressed = true;
            break;
        }
    }

    return pressed;
}

extern "C" void main() {
    constexpr gpio_num_t red_pin = GPIO_NUM_14;
    constexpr gpio_num_t green_pin = GPIO_NUM_12;
    constexpr gpio_num_t blue_pin = GPIO_NUM_13;
    constexpr gpio_num_t switch_pin = GPIO_NUM_5;

    validate_led_pins<red_pin, green_pin, blue_pin>();
    validate_switch_pin<switch_pin>();

    Led led(red_pin, green_pin, blue_pin);
    Serial serial(74880);
    Switch sw(switch_pin);

    uart_printf("Initialized\r\n");

    Timer timer;
    uart_printf("Start timer\r\n");
    timer.init_tick();
    LightSetColor(led, Color::OFF);

    for (;;) {
        uart_printf("Loop\r\n");
        bool pressed = has_been_pushed(sw, timer, 10000u);
        set_color_for_ms(led, pressed ? Color::GREEN : Color::RED, timer, 10000u);
    }
}

