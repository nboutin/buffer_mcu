cmake_minimum_required(VERSION 3.28)
project(buffer_mcu_ut)

include(CTest)
enable_testing()

include(cmake/get_cpm.cmake)
include(cmake/CPM.cmake)
CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  VERSION 1.13.0
  OPTIONS
    "INSTALL_GTEST OFF"
    "gtest_force_shared_crt ON"
)

add_executable(${PROJECT_NAME}
  suites/ut_buf_clear.cpp
  suites/ut_buf_compare.cpp
  suites/ut_buf_fill_pattern.cpp
  suites/ut_buf_get_free_size.cpp
  suites/ut_buf_get_read_write.cpp
  suites/ut_buf_get_size.cpp
  suites/ut_buf_get_to_read_count.cpp
  suites/ut_buf_get_used_size.cpp
  suites/ut_buf_init_empty.cpp
  suites/ut_buf_init_full.cpp
  suites/ut_buf_is_full.cpp
  suites/ut_buf_make_view_full.cpp
  suites/ut_buf_make_view_to_read.cpp
  suites/ut_buf_reset_read_index.cpp
  suites/ut_buf_reset.cpp
  suites/ut_buf_set_all_read.cpp
  suites/ut_buf_set_size.cpp
  suites/ut_buf_write_copy.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE buffer_mcu GTest::gmock_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
