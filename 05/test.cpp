#include <chrono>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day05, part1) {
    EXPECT_EQ(part1("../05/test_input"), std::string("CMZ"));
}

TEST(day05, part2) {
    EXPECT_EQ(part2("../05/test_input"), std::string("MCD"));
}
