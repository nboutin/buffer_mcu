cmake_minimum_required(VERSION 3.28)
project(buffer_mcu)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUFFER_MCU_TEST "Build Buffer MCU Tests" ON)
option(USE_CPM "Import dependencies with CPM" OFF)
option(USE_FETCH "Import dependency with Fetch" ON)

if(BUFFER_MCU_TEST)
    include(CTest)
    if(USE_FETCH)
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest
            GIT_TAG        v1.14.0
          )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    if(USE_CPM)
        include(cmake/test_config.cmake)
    endif()
endif()

# ---

add_library(${PROJECT_NAME} OBJECT
    source/buffer.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include)

if(BUFFER_MCU_TEST)
    add_subdirectory(test)
endif()
