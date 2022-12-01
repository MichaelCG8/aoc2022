#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day{{cookiecutter.day}}, part1) {
    EXPECT_EQ(part1("../{{"{:>02s}".format(cookiecutter.day)}}/test_input"), 0);
}

TEST(day{{cookiecutter.day}}, part2) {
    EXPECT_EQ(part2("../{{"{:>02s}".format(cookiecutter.day)}}/test_input"), 0);
}
