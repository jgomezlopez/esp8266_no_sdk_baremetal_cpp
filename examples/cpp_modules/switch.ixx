export module switch_hal;

extern "C" {
#include <esp8266.h>
}

export class Switch {
public:
    explicit Switch(gpio_num_t pin)
        : pin_(pin)
    {
        gpio_pullup_en(pin_);
        gpio_output_disable(pin_);
    }

    bool switch_pushed(this Switch& self) {
        return gpio_get_level(self.pin_) == LOW;
    }

    bool switch_pushed(this const Switch& self) { return false; }

private:
    gpio_num_t pin_;
};

