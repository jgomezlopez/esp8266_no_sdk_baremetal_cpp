cmake_minimum_required(VERSION 4.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../../toolchain-xtensa.cmake)

#set(CMAKE_C_FLAGS "-nostartfiles -Wall -ffreestanding -Isrc/include -g -Wl,-static -Wl,--gc-sections -Wl,-EL")
#set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti -std=c++23 -nostartfiles -Wall -ffreestanding -Isrc/include -g -Wl,-static -Wl,--gc-sections -Wl,-EL")
#set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,-Map=firmware.map -Wl,--gc-sections -Wl,-EL")

set(CMAKE_C_FLAGS "-nostartfiles -Wall -ffreestanding -Isrc/include -Wl,-static -Wl,--gc-sections -Wl,-EL")
#set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti -std=c++23 -nostartfiles -Wall -ffreestanding -Isrc/include -Wl,-static -Wl,--gc-sections -Wl,-EL")
set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti -fno-inline -fno-inline-functions -fno-inline-small-functions -fno-default-inline -std=c++23 -nostartfiles -Wall -ffreestanding -Isrc/include -Wl,-static -Wl,--gc-sections -Wl,-EL")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Wl,-Map=firmware.map -Wl,--gc-sections -Wl,-EL")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##################################################################
# IMPORTAN!: Comment the following line to not force not inlining
##################################################################
add_compile_options(-fno-inline -fno-inline-functions -fno-inline-small-functions -fno-default-inline)

project(cpp_independent_modules LANGUAGES C CXX ASM)

include_directories(
    ${CMAKE_SOURCE_DIR}/../../src/include
    ${CMAKE_SOURCE_DIR}
)

file(GLOB_RECURSE CORE_C   ${CMAKE_SOURCE_DIR}/../../src/*.c)
file(GLOB_RECURSE CORE_S   ${CMAKE_SOURCE_DIR}/../../src/arch/*.S)

add_library (core OBJECT ${CORE_C} ${CORE_S})

add_library (hal)
add_library (hal_timer)

target_compile_options(hal PRIVATE -O3)
target_compile_options(hal_timer PRIVATE -O0)

target_sources (hal PUBLIC FILE_SET CXX_MODULES FILES 
			color.cppm 
			concepts.cppm 
		      	serial.cppm
		       	switch.cppm
		       	led.cppm
		       	validation.cppm)

target_sources (hal PRIVATE 
		      	serial_impl.cppm
		       	switch_impl.cppm
		       	led_impl.cppm)

target_sources (hal_timer PUBLIC FILE_SET CXX_MODULES FILES 
		       	timer.cppm)

target_sources (hal_timer PRIVATE 
		       	timer_impl.cppm)


add_executable(cpp_independent_modules main.cpp)

target_link_options(cpp_independent_modules PRIVATE
    -T${CMAKE_SOURCE_DIR}/../../src/ld/linker.ld
)

target_link_libraries(cpp_independent_modules PRIVATE core)
target_link_libraries(cpp_independent_modules PRIVATE hal)
target_link_libraries(cpp_independent_modules PRIVATE hal_timer)
target_link_libraries(cpp_independent_modules PRIVATE c gcc m)
