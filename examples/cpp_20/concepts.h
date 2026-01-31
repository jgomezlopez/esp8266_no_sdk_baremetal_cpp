#pragma once
#include "color.h"

template<typename T>
concept is_void = __is_same(T, void);

template<typename T>
concept is_bool = __is_same(T, bool);

template<typename T>
concept LightConcept = requires(T strategy, Color light) {
    { strategy.set_color(light) } -> is_void;
};

template<typename T>
concept SwitchConcept = requires(T strategy) {
    { strategy.switch_pushed() } -> is_bool;
};

