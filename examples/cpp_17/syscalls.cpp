extern "C" {
    #include <stddef.h>
    #include <stdint.h>
}

// ============================================================
// 1. __cxa_pure_virtual
// ============================================================

extern "C" void __cxa_pure_virtual() {
    while (true) {}
}

// ============================================================
// 2. Heap estático + _sbrk
// ============================================================

static uint8_t heap_area[8 * 1024];
static size_t heap_pos = 0;

extern "C" void* _sbrk(ptrdiff_t increment) {
    if (increment < 0) {
        return (void*)-1;
    }

    if (heap_pos + increment > sizeof(heap_area)) {
        return (void*)-1;
    }

    void* prev = &heap_area[heap_pos];
    heap_pos += increment;
    return prev;
}

