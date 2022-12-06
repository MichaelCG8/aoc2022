#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day06, part1) {
    EXPECT_EQ(part1("../06/test_input_0"), 7);
    EXPECT_EQ(part1("../06/test_input_1"), 5);
    EXPECT_EQ(part1("../06/test_input_2"), 6);
    EXPECT_EQ(part1("../06/test_input_3"), 10);
    EXPECT_EQ(part1("../06/test_input_4"), 11);
}

TEST(day06, part2) {
    EXPECT_EQ(part2("../06/test_input_5"), 19);
    EXPECT_EQ(part2("../06/test_input_6"), 23);
    EXPECT_EQ(part2("../06/test_input_7"), 23);
    EXPECT_EQ(part2("../06/test_input_8"), 29);
    EXPECT_EQ(part2("../06/test_input_9"), 26);
}
