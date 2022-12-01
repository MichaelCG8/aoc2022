#! /usr/bin/env bash

dayStr=$(printf "%02d" "$1")

cp -r template "$dayStr"

echo "" >> CMakeLists.txt
echo "add_executable(day"$dayStr" "$dayStr"/main.cpp "$dayStr"/lib.cpp "$dayStr"/lib.h)" >> CMakeLists.txt
echo "add_executable(day"$dayStr"_test "$dayStr"/test.cpp "$dayStr"/lib.cpp "$dayStr"/lib.h)" >> CMakeLists.txt
echo "target_link_libraries(day"$dayStr"_test GTest::gtest_main)" >> CMakeLists.txt
echo "gtest_discover_tests(day"$dayStr"_test)" >> CMakeLists.txt
