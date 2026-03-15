export module led;

import color;

extern "C" {
#include <esp8266.h>
}

export class Led {
public:
    explicit Led(gpio_num_t r, gpio_num_t g, gpio_num_t b);
    void set_color(this Led& self, Color c); 
    void set_color(this const Led& self, Color c) {}

private:
    gpio_num_t red_, green_, blue_;
    void set_rgb(bool r, bool g, bool b); 
};

