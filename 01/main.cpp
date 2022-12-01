#include <chrono>
#include <iostream>

#include "lib.h"


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = part1("01/input");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Part 1: " << result1 << ", time [us]: " << duration.count() << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    auto result2 = part2("01/input");
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Part 2: " << result2 << ", time [us]: " << duration.count() << std::endl;
    
    return 0;
}
