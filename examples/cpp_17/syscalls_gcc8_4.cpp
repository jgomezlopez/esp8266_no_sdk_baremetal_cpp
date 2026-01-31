// syscalls.cpp — runtime mínimo para newlib + C++ freestanding

extern "C" {
    #include <stddef.h>
    #include <stdint.h>
    #include <sys/reent.h>
}

// ============================================================
// 1. __cxa_pure_virtual  (necesario para clases abstractas)
// ============================================================

extern "C" void __cxa_pure_virtual() {
    while (true) {}
}

// ============================================================
// 2. __getreent  (newlib reentrante lo exige)
// ============================================================

extern "C" struct _reent* _global_impure_ptr;

extern "C" struct _reent* __getreent() {
    return _global_impure_ptr;
}

// ============================================================
// 3. Heap estático + _sbrk_r + _sbrk
// ============================================================

static uint8_t heap_area[8 * 1024];   // Ajusta tamaño según tu RAM
static size_t heap_pos = 0;

extern "C" void* _sbrk_r(struct _reent* r, ptrdiff_t increment) {
    (void)r;

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

extern "C" void* _sbrk(ptrdiff_t increment) {
    return _sbrk_r(_global_impure_ptr, increment);
}

