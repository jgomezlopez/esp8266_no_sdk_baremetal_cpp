# ESP8266 No-SDK Framework
A lightweight framework for experimenting with the ESP8266 architecture without using the official SDK.
This project is designed for learning purposes — to understand the ESP8266 memory map, UART, interrupts, and peripheral handling at the bare-metal level.

## Requirements
- Xtensa lx106 toolchain (gcc 15). For cpp_baseline or cpp_17 examples you can use [Link](https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz)
- CMake 4.2.1. For cpp_baseline or cpp_17 examples you can use CMake 3.28.
- Esptool.
All the requirements can be found in the Podman container created in the repo [Link](https::/)

## Build
`cd examples/<project_name>`
`./build.sh build`

## clean
`cd examples/<project_name>`
`./build.sh clean`

## Elf2Image and flash
`cd examples/<project_name>`
`./build.sh clean`

## All
`cd examples/<project_name>`
`./build.sh clean`

## NOTE
- This is for experimenting with ESP8266's architecture so most of the functionality will not work.
- This is basic framework so we can't use SPI flash to execute program in ESP8266. (Or maybe I am too dump to make it work)
- To learn about memmory mapping and register mapping of ESP8266, read docs.md file.

## Examples

All the examples except cpp_baseline consist in a switch, if it pushed switch a LED on in green otherwise a LED is switch itself in red.

### Wiring

![Schema ESP8266 with RGB LED and push button switch](./image/Diagram.png)

### Flowchart

![Flow chart RGB LED and push button switch](./image/Flowchart.png)

### Examples

The features of examples shown in the following table, are created to validate the toolchain built using the repo [Link](https://)
|Folder|Features|GCC version|C++ version|
|------|--------|-----------|-----------|
|cpp_baseline||8.4 and above|C++17|
|cpp_17|Virtual methods|8.4 and above|C++17|
|cpp_20|Concepts|15.2|C++20|
|cpp_23|Concepts, deduced this|15.2|C++23|
|cpp_modules|Concepts, Modules, deduced this|15.2|C++23|

### Energy measurement

A USB Power tester was used to measure the energy consumption of each example running in a ESP-8266 NodeMCU board with the wiring shown above.

The baseline (hardware baseline consumption) is shown in the folowing table:

| Folder | LED | mWh (12h) |
|--------|-----|-----------|
| cp_baseline | Red | 2570 |
| cp_baseline | Off | 2386 |

The average 2476 mWh (6h LED in red, 6h LED off and 12h switch enabled waiting to be pushed) is the energy consumption of the hardware baseline. This average is substracted to each example to estimate Sotfware energy consumption of the presented example running in a ESP-8266 NodeMCU board.

The energy consumption of each example running in a ESP-8266 board for 12h is shown in the following table:
 
| Folder | GCC version | Virtual methods | Concepts | Deduced this | Modules | mWh (12h hardware consumption) | mWh (12h software consumption) |
|------------------|------------|
|cpp_17|8.4|✅|❌|❌|❌|2704|226|
|cpp_17|15.2|✅|❌|❌|❌|2702|224|
|cpp_20|15.2|❌|✅|❌|❌|2600|122|
|cpp_23||15.2|❌|✅|✅|❌|2602|124|
|cpp_modules|15.2|❌|✅|✅|✅|2713|235|



