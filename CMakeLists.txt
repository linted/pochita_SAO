cmake_minimum_required(VERSION 2.13)
project(test C)

add_executable(test test.c)
target_include_directories(test PUBLIC ${MSP430_INSTALL_DIR}/include)
target_link_options(test PUBLIC -L ${MSP430_INSTALL_DIR}/include/ -T msp430fr2433.ld -Wl,--gc-sections)
target_compile_options(test PUBLIC -nostdlib -static -mmcu=msp430fr2433 -O1)
# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
