#include <iostream>

#include "../aoc.h"
#include "lib.h"


int main() {
    auto result1 = part1("02/input");
    std::cout << "Part 1: " << result1 << std::endl;
    time_execution(&part1, "02/input", 1000);
    
    auto result2 = part2("02/input");
    std::cout << "Part 2: " << result2 << std::endl;
    time_execution(&part2, "02/input", 1000);
    
    return 0;
}
