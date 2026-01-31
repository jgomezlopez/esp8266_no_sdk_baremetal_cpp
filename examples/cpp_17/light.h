#pragma once
#include "color.h"

class Light {
public:
    virtual ~Light() {}

    virtual void set_color(Color::Name c) = 0;
};

