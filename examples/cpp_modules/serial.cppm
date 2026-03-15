export module serial;

import color;

extern "C" {
#include <esp8266.h>
#include <stdio.h>
}

export class Serial {
public:
    explicit Serial(uint32_t speed);
    void set_color(this Serial&, Color c);
};

