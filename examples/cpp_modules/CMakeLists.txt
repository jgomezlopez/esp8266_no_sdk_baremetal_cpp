cmake_minimum_required(VERSION 4.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../../toolchain-xtensa.cmake)

#set(CMAKE_C_FLAGS "-nostartfiles -Wall -ffreestanding -Isrc/include -g -Wl,-static -Wl,--gc-sections -Wl,-EL")
#set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti -std=c++23 -nostartfiles -Wall -ffreestanding -Isrc/include -g -Wl,-static -Wl,--gc-sections -Wl,-EL")
#set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,-Map=firmware.map -Wl,--gc-sections -Wl,-EL")

set(CMAKE_C_FLAGS "-nostartfiles -Wall -ffreestanding -Isrc/include -g -Wl,-static -Wl,-EL")
set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti -std=c++23 -nostartfiles -Wall -ffreestanding -Isrc/include -g -Wl,-static -Wl,-EL")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,-Map=firmware.map -Wl,-EL")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-O0)

project(cpp_modules LANGUAGES C CXX ASM)

include_directories(
    ${CMAKE_SOURCE_DIR}/../../src/include
)

file(GLOB_RECURSE CORE_C   ${CMAKE_SOURCE_DIR}/../../src/*.c)
file(GLOB_RECURSE CORE_S   ${CMAKE_SOURCE_DIR}/../../src/arch/*.S)

add_library (core OBJECT ${CORE_C} ${CORE_S})

add_library (hal OBJECT)

target_sources (hal PUBLIC FILE_SET CXX_MODULES FILES 
		       	timer.ixx
			color.ixx 
			concepts.ixx 
		      	serial.ixx
		       	switch.ixx
		       	led.ixx
		       	validation.ixx)

add_executable(cpp_modules main.cpp)

target_link_options(cpp_modules PRIVATE
    -T${CMAKE_SOURCE_DIR}/../../src/ld/linker.ld
)

target_link_libraries(cpp_modules PRIVATE core)
target_link_libraries(cpp_modules PRIVATE hal)
target_link_libraries(cpp_modules PRIVATE c gcc m)
