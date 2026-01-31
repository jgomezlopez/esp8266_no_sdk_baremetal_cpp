# ============================================
# Toolchain Xtensa ESP8266 (GCC auto C++17/C++23)
# ============================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR xtensa)

# Prefijo del toolchain
set(TOOLCHAIN_PREFIX xtensa-lx106-elf)

# Compiladores
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)

# Estándar C
set(CMAKE_C_STANDARD 11)

# ============================================================
# Detectar versión del compilador C++
# ============================================================

# Forzar detección temprana
execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
    OUTPUT_VARIABLE GCC_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Xtensa GCC detectado: versión ${GCC_VERSION}")

# Selección automática del estándar C++
if (GCC_VERSION VERSION_GREATER_EQUAL "15.0")
    message(STATUS "Usando C++23 para GCC >= 15")
    set(CMAKE_CXX_STANDARD 23)
elseif (GCC_VERSION VERSION_GREATER_EQUAL "8.4" AND GCC_VERSION VERSION_LESS "8.5")
    message(STATUS "Usando C++17 para GCC 8.4.x")
    set(CMAKE_CXX_STANDARD 17)
else()
    message(WARNING "Versión GCC no reconocida, usando C++17 por defecto")
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================
# Flags C
# ============================================================

set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -nostartfiles -Wall -Wextra -g -O0")

# ============================================================
# Flags C++
# ============================================================

set(CMAKE_CXX_FLAGS "-ffreestanding -nostdlib -nostartfiles -Wall -Wextra -g -O0 -fno-exceptions -fno-rtti")

# ============================================================
# Flags del linker
# ============================================================

set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,--gc-sections -Wl,-EL")

# ============================================================
# Evitar buscar librerías del host
# ============================================================

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
