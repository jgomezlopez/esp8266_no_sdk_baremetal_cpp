cmake_minimum_required(VERSION 3.28)
project(cpp_classic LANGUAGES C CXX ASM)

# Toolchain Xtensa
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../../toolchain-xtensa.cmake)

# ============================================================
# 1. FLAGS EQUIVALENTES AL MAKEFILE (sin -c)
# ============================================================

set(CMAKE_C_FLAGS "-nostartfiles -Wall -ffreestanding -Isrc/include -Wl,-static -Wl,--gc-sections -Wl,-EL")
set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti -std=c++23 -nostartfiles -Wall -ffreestanding -Isrc/include -Wl,-static -Wl,--gc-sections -Wl,-EL")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,-Map=firmware.map -Wl,--gc-sections -Wl,-EL")

set(CMAKE_VERBOSE_MAKEFILE ON)
# ============================================================
# 2. INCLUDES
# ============================================================

include_directories(
    ${CMAKE_SOURCE_DIR}/../../src/include
)

# ============================================================
# 3. CORE: SOLO C + ASM (igual que Makefile)
# ============================================================

file(GLOB_RECURSE CORE_C   ${CMAKE_SOURCE_DIR}/../../src/*.c)
file(GLOB_RECURSE CORE_S   ${CMAKE_SOURCE_DIR}/../../src/arch/*.S)

# ============================================================
# 4. EJEMPLO: SOLO main.cpp (igual que Makefile)
# ============================================================

add_library (core OBJECT ${CORE_C} ${CORE_S})

add_library (hal)
add_library (hal_timer)

target_compile_options(hal PRIVATE -O3)
target_compile_options(hal_timer PRIVATE -O0)

target_sources (hal PRIVATE 
		      	serial.cpp
		       	switch.cpp
		       	led.cpp)

target_sources (hal_timer PRIVATE 
		       	cpp_timer.cpp)

add_executable(cpp_classic
    main.cpp
)

# ============================================================
# 5. LINKER SCRIPT (orden correcto)
# ============================================================

target_link_options(cpp_classic PRIVATE
    -T${CMAKE_SOURCE_DIR}/../../src/ld/linker.ld
)

# ============================================================
# 6. LIBRERÍAS (igual que Makefile)
# ============================================================

target_link_libraries(cpp_classic PRIVATE core)
target_link_libraries(cpp_classic PRIVATE hal)
target_link_libraries(cpp_classic PRIVATE hal_timer)
target_link_libraries(cpp_classic PRIVATE c gcc m)

