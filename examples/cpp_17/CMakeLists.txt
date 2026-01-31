set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../../toolchain-xtensa.cmake)

cmake_minimum_required(VERSION 3.28)
project(cpp_17 LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Isrc/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Isrc/include -fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,-Map=firmware.map -Wl,--gc-sections -Wl,-EL")
add_compile_options(-fno-sized-deallocation)

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
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10.0")
    message(STATUS "Usando syscalls para GCC 8.x")
    add_executable(cpp_17
        ${CORE_C}
        ${CORE_S}
        cpp_timer.cpp
        serial.cpp
        switch.cpp
        led.cpp
        memory.cpp
        syscalls_gcc8_4.cpp
        main.cpp
    )
else()
    message(STATUS "Usando syscalls para GCC 15.x")
    add_executable(cpp_17
        ${CORE_C}
        ${CORE_S}
        cpp_timer.cpp
        serial.cpp
        switch.cpp
        led.cpp
        memory.cpp
        syscalls.cpp
        main.cpp
    )
endif()
# ============================================================
# 5. LINKER SCRIPT (orden correcto)
# ============================================================

target_link_options(cpp_17 PRIVATE
    -T${CMAKE_SOURCE_DIR}/../../src/ld/linker.ld
)

# ============================================================
# 6. LIBRERÍAS (igual que Makefile)
# ============================================================

target_link_libraries(cpp_17
    c
    gcc
    m
)

