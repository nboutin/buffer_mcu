cmake_minimum_required(VERSION 3.28)
project(buffer_mcu)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(BUFFER_MCU_TEST)
    include(cmake/test_config.cmake)
endif()

add_library(${PROJECT_NAME} OBJECT
    source/buffer.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include)

if(BUFFER_MCU_TEST)
    add_subdirectory(test)
endif()
