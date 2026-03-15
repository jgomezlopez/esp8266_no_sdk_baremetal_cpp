export module timer;

extern "C" {
#include <esp8266.h>
}

export class Timer {
public:
    Timer() = default;
    void init_tick(); 
    uint32_t now() const;
    void delay(uint32_t ms);

private:
    bool initialized_ = false;
    inline static uint32_t g_ms_ = 0;
    [[gnu::used]]
    static void isr_handler(void*); 
};

