export module color;

extern "C" {
#include <stdint.h>
}

export enum class Color : uint8_t {
    OFF, RED, GREEN, BLUE, YELLOW, PURPLE, CYAN, WHITE
};

