cmake_minimum_required(VERSION 2.13)
project(test C)

message("Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

add_executable(pochita_firmware test.c i2c_stuff.c)
target_include_directories(pochita_firmware PUBLIC ${MSP430_INSTALL_DIR}/include)
target_link_options(pochita_firmware PUBLIC -L ${MSP430_INSTALL_DIR}/include/ -T msp430g2121.ld -Wl,--gc-sections -nostdlib -static -mmcu=msp430g2121)
target_compile_options(pochita_firmware PUBLIC -nostdlib -static -mmcu=msp430g2121 -O1)
