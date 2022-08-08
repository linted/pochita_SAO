cmake_minimum_required(VERSION 2.13)
project(pochita C)

message("Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

add_executable(pochita_firmware test.c) #i2c_stuff.c)
target_include_directories(pochita_firmware PUBLIC ${MSP430_INSTALL_DIR}/msp430-elf/include/ ${MSP430_INSTALL_DIR}/include)
target_link_options(pochita_firmware PUBLIC -L ${MSP430_INSTALL_DIR}/include/ -T ${MSP430_INSTALL_DIR}/include/msp430g2121.ld -mcpu=MSP430X -mmcu=msp430g2121 -static -g)
# target_compile_options(pochita_firmware PUBLIC -mcpu=msp430xv2 -mmcu=msp430g2121 -mhwmult=none -c -O0 -g3 -ggdb -gdwarf-2 -Wall -Werror -Wextra -Wshadow -std=gnu11 -Wpedantic -MMD)
target_compile_options(pochita_firmware PUBLIC -nostdlib -static -mcpu=MSP430X -mmcu=msp430g2121 -Os -DDEPRECATED -Wl,--verbose)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug") 
    target_compile_options(pochita_firmware PUBLIC -g3)
endif()