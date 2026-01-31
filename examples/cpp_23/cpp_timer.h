#pragma once

extern "C" {
#include <core/system.h>
#include <esp8266.h>
#include <stdint.h>
}

class Timer {
public:
    Timer() = default;
    void init_tick();
    uint32_t now() const;
    void delay(uint32_t ms);

private:
    bool initialized_ = false;
    inline static uint32_t g_ms_ = 0;
    static void isr_handler(void*); 
};

