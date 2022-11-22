#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "lib.hpp"

TEST(template, basic_assertion) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
