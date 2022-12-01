#! /usr/bin/env python 

day = "{{"{:>02}".format(cookiecutter.day)}}"
new_text = f"""
add_executable(day{day} {day}/main.cpp {day}/lib.cpp {day}/lib.h)
add_executable(day{day}_test {day}/test.cpp {day}/lib.cpp {day}/lib.h)
target_link_libraries(day{day}_test GTest::gtest_main)
gtest_discover_tests(day{day}_test)
"""

with open("../CMakeLists.txt", "a") as f:
	f.write(new_text)
