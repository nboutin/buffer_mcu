cmake_minimum_required(VERSION 3.28)
project(buffer_mcu)

add_library(${PROJECT_NAME} OBJECT
    source/buffer.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include)

add_subdirectory(test)
