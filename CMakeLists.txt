cmake_minimum_required(VERSION 3.28)
project(buffer_mcu)

set(target_name buffer_mcu)

add_library(${target_name} OBJECT
    source/buffer.c)

target_include_directories(${target_name}
    PUBLIC
        include)

add_subdirectory(test)
