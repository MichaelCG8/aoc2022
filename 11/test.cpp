#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day11, part1) {
    EXPECT_EQ(part1<4>("../11/test_input"), 10605);
}

TEST(day11, part2) {
    EXPECT_EQ(part2<4>("../11/test_input"), 2713310158);
}
