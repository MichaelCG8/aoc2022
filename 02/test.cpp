#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day02, part1) {
    EXPECT_EQ(part1("../02/test_input"), 15);
}

TEST(day02, part2) {
    EXPECT_EQ(part2("../02/test_input"), 12);
}
