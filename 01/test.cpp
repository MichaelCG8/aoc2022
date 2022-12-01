#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day01, part1) {
    EXPECT_EQ(part1("../01/test_input"), 24000);
}

TEST(day01, part2) {
    EXPECT_EQ(part2("../01/test_input"), 45000);
}
