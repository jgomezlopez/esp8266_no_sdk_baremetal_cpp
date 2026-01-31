// memory.cpp
extern "C" {
    #include <stddef.h>   // size_t válido en freestanding
    void* malloc(size_t);
    void  free(void*);
}

// new / delete escalares
void* operator new(size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) noexcept {
    if (ptr) free(ptr);
}

// sized delete (GCC 15 la genera incluso en C++14)
void operator delete(void* ptr, size_t) noexcept {
    if (ptr) free(ptr);
}

// new[] / delete[]
void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void* ptr) noexcept {
    if (ptr) free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept {
    if (ptr) free(ptr);
}

