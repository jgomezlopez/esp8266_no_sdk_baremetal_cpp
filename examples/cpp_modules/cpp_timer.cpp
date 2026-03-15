#include "cpp_timer.h"

void Timer::init_tick() {
    if (initialized_) return;

    timer_init_t cfg{
        .clkdiv   = TIMER_CLKDIV_256,
        .int_type = TIMER_EDGE,
        .autoload = 1u,
        .time_ms  = 1u
    };

    timer_init(cfg);
    timer_clr_int();
    timer_isr_attach(&Timer::isr_handler, nullptr);
    timer_enable(1);

    initialized_ = true;
}

uint32_t Timer::now() const {
    return g_ms_;
}

void Timer::delay(uint32_t ms) {
    uint32_t start = now();
    while ((now() - start) < ms) {}
}

void Timer::isr_handler(void*) {
    timer_clr_int();
    g_ms_++;
}

