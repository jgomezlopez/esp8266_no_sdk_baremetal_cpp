#pragma once

extern "C" {
#include <esp8266.h>
#include <stdio.h>
}

#include "color.h"
#include "light.h"

class Serial : public Light {
public:
    explicit Serial(const uint32_t speed);
    void set_color(Color::Name c) override;
};

