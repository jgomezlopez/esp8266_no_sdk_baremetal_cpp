#pragma once

extern "C" {
#include <esp8266.h>
#include <stdio.h>
}

#include "color.h"

class Serial {
public:
    explicit Serial(const uint32_t speed);
    void set_color(Color c);
};

