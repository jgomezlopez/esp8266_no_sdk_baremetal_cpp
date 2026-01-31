#include "led.h"

Led::Led(gpio_num_t r, gpio_num_t g, gpio_num_t b)
    : red_(r), green_(g), blue_(b)
{
    reset_pins();

    gpio_output_enable(red_);
    gpio_output_enable(green_);
    gpio_output_enable(blue_);
    set_color(Color::OFF);
}

void Led::set_color(Color::Name c) {
    switch (c) {
        case Color::OFF:    set_rgb(false,false,false); break;
        case Color::RED:    set_rgb(true,false,false);  break;
        case Color::GREEN:  set_rgb(false,true,false);  break;
        case Color::BLUE:   set_rgb(false,false,true);  break;
        case Color::YELLOW: set_rgb(true,true,false);   break;
        case Color::PURPLE: set_rgb(true,false,true);   break;
        case Color::CYAN:   set_rgb(false,true,true);   break;
        case Color::WHITE:  set_rgb(true,true,true);    break;
    }
}

void Led::set_rgb(bool r, bool g, bool b) {
    gpio_set_level(red_,   r ? HIGH : LOW);
    gpio_set_level(green_, g ? HIGH : LOW);
    gpio_set_level(blue_,  b ? HIGH : LOW);
}

