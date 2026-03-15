export module switch_hal;

extern "C" {
#include <esp8266.h>
}

export class Switch {
public:
    explicit Switch(gpio_num_t pin);
    bool switch_pushed(this Switch& self); 
    bool switch_pushed(this const Switch& self) { return false; }

private:
    gpio_num_t pin_;
};

