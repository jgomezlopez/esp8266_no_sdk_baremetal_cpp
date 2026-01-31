#include "switch.h"

Switch::Switch(gpio_num_t pin)
    : pin_(pin)
{
    gpio_pullup_en(pin_);
    gpio_output_disable(pin_);
}

bool Switch::switch_pushed() {
    return gpio_get_level(pin_) == LOW;
}

