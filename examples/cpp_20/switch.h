#pragma once

extern "C" {
#include <esp8266.h>
}

class Switch {
public:
    explicit Switch(const gpio_num_t pin);
    bool switch_pushed() const { return false; }
    bool switch_pushed();

private:
    gpio_num_t pin_;
};

