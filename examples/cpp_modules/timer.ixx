export module timer;

extern "C" {
#include <esp8266.h>
}

export class Timer {
public:
    Timer() = default;

    void init_tick() {
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

    uint32_t now() const {
        return g_ms_;
    }

    void delay(uint32_t ms) {
        uint32_t start = now();
        while ((now() - start) < ms) {}
    }

private:
    bool initialized_ = false;
    inline static uint32_t g_ms_ = 0;

    static void isr_handler(void*) {
        timer_clr_int();
        g_ms_++;
    }
};

