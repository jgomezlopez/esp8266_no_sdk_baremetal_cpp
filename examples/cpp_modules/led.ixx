export module led;

import color;

extern "C" {
#include <esp8266.h>
}

export class Led {
public:
    explicit Led(gpio_num_t r, gpio_num_t g, gpio_num_t b)
        : red_(r), green_(g), blue_(b)
    {
        reset_pins();

        gpio_output_enable(red_);
        gpio_output_enable(green_);
        gpio_output_enable(blue_);
        set_color(Color::OFF);
    }

    void set_color(this Led& self, Color c) {
        using enum Color;
        switch (c) {
            case OFF:    self.set_rgb(false,false,false); break;
            case RED:    self.set_rgb(true,false,false);  break;
            case GREEN:  self.set_rgb(false,true,false);  break;
            case BLUE:   self.set_rgb(false,false,true);  break;
            case YELLOW: self.set_rgb(true,true,false);   break;
            case PURPLE: self.set_rgb(true,false,true);   break;
            case CYAN:   self.set_rgb(false,true,true);   break;
            case WHITE:  self.set_rgb(true,true,true);    break;
        }
    }

    void set_color(this const Led& self, Color c) {}

private:
    gpio_num_t red_, green_, blue_;

    void set_rgb(bool r, bool g, bool b) {
        gpio_set_level(red_,   r ? HIGH : LOW);
        gpio_set_level(green_, g ? HIGH : LOW);
        gpio_set_level(blue_,  b ? HIGH : LOW);
    }
};

