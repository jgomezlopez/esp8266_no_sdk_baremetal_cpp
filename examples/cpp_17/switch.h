#pragma once

extern "C" {
#include <esp8266.h>
}

#include "trigger.h"

class Switch : public Trigger {
public:
    explicit Switch(const gpio_num_t pin);
    bool switch_pushed() const { return false; }
    bool switch_pushed() override;

private:
    gpio_num_t pin_;
};

