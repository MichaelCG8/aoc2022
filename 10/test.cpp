#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.h"

TEST(day10, part1) {
    EXPECT_EQ(part1("../10/test_input"), 13140);
}

TEST(day10, part2) {
    EXPECT_EQ(
        part2("../10/test_input"),
        "##..##..##..##..##..##..##..##..##..##.."
        "###...###...###...###...###...###...###."
        "####....####....####....####....####...."
        "#####.....#####.....#####.....#####....."
        "######......######......######......####"
        "#######.......#######.......#######....."
    );
}
