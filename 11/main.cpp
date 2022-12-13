#include <iostream>

#include "../aoc.h"
#include "lib.h"


#define N_TIMING_RUNS (1000)


int main() {
    auto result1 = part1<8>("11/input");
    std::cout << "Part 1: " << result1 << std::endl;
    time_execution(&part1<8>, "11/input", N_TIMING_RUNS);
    
    auto result2 = part2<8>("11/input");
    std::cout << "Part 2: " << result2 << std::endl;
    time_execution(&part2<8>, "11/input", N_TIMING_RUNS);
    
    return 0;
}
