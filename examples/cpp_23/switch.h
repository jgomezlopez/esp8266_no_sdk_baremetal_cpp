#pragma once

extern "C" {
#include <esp8266.h>
}

class Switch {
public:
    explicit Switch(const gpio_num_t pin);
    bool switch_pushed(this const Switch& self) { return false; }
    bool switch_pushed(this Switch& self);

private:
    gpio_num_t pin_;
};

