cmake_minimum_required(VERSION 3.20)
project(aoc2022)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(
    -Wall
    -Werror
    -Wextra
    -Wpedantic
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

add_executable(day01 01/main.cpp 01/lib.cpp 01/lib.h)
add_executable(day01_test 01/test.cpp 01/lib.cpp 01/lib.h)
target_link_libraries(day01_test GTest::gtest_main)
gtest_discover_tests(day01_test)

add_executable(day02 02/main.cpp 02/lib.cpp 02/lib.h)
add_executable(day02_test 02/test.cpp 02/lib.cpp 02/lib.h)
target_link_libraries(day02_test GTest::gtest_main)
gtest_discover_tests(day02_test)

add_executable(day03 03/main.cpp 03/lib.cpp 03/lib.h)
add_executable(day03_test 03/test.cpp 03/lib.cpp 03/lib.h)
target_link_libraries(day03_test GTest::gtest_main)
gtest_discover_tests(day03_test)

add_executable(day04 04/main.cpp 04/lib.cpp 04/lib.h)
add_executable(day04_test 04/test.cpp 04/lib.cpp 04/lib.h)
target_link_libraries(day04_test GTest::gtest_main)
gtest_discover_tests(day04_test)

add_executable(day05 05/main.cpp 05/lib.cpp 05/lib.h)
add_executable(day05_test 05/test.cpp 05/lib.cpp 05/lib.h)
target_compile_definitions(day05_test PRIVATE TESTING)
target_link_libraries(day05_test GTest::gtest_main)
gtest_discover_tests(day05_test)

add_executable(day06 06/main.cpp 06/lib.cpp 06/lib.h)
add_executable(day06_test 06/test.cpp 06/lib.cpp 06/lib.h)
target_link_libraries(day06_test GTest::gtest_main)
gtest_discover_tests(day06_test)
