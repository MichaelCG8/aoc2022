#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day03, part1) {
    EXPECT_EQ(part1("../03/test_input"), 157);
}

TEST(day03, part2) {
    EXPECT_EQ(part2("../03/test_input"), 70);
}
