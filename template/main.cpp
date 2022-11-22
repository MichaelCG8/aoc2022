#include <chrono>
#include <iostream>

#include "lib.hpp"


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = part1();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Part 1: " << part1() << ", time [ms]: " << duration.count() << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    auto result2 = part2();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Part 2: " << part1() << ", time [ms]: " << duration.count() << std::endl;
    
    return 0;
}
