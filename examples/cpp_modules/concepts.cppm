export module concepts;

import color;

export template<typename T>
concept is_void = __is_same(T, void);

export template<typename T>
concept is_bool = __is_same(T, bool);

export template<typename T>
concept LightConcept = requires(T strategy, Color light) {
    { strategy.set_color(light) } -> is_void;
};

export template<typename T>
concept SwitchConcept = requires(T strategy) {
    { strategy.switch_pushed() } -> is_bool;
};

