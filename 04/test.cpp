#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day04, part1) {
    EXPECT_EQ(part1("../04/test_input"), 2);
}

TEST(day04, part2) {
    EXPECT_EQ(part2("../04/test_input"), 4);
}
