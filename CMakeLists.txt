cmake_minimum_required(VERSION 3.20)
project(aoc2022)

set(CMAKE_CXX_STANDARD 17)
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
