#pragma once

extern "C" {
#include <esp8266.h>
}

#include "color.h"

class Led {
public:
    explicit Led(const gpio_num_t r, const gpio_num_t g, const gpio_num_t b);
    void set_color(Color c);
    void set_color(Color c) const {}
private:
    gpio_num_t red_, green_, blue_;
    void set_rgb(bool r, bool g, bool b);
};

