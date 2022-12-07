#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day07, part1) {
    EXPECT_EQ(part1("../07/test_input"), 95437);
    EXPECT_EQ(part1("../07/input"), 1845346);
}

TEST(day07, part2) {
    EXPECT_EQ(part2("../07/test_input"), 24933642);
    EXPECT_EQ(part2("../07/input"), 3636703);
}
