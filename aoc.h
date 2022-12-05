#ifndef AOC22_AOC_H
#define AOC22_AOC_H

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>


template<typename T>
void time_execution(T (*func)(const char*), const char* path, int runs) {
    // Save all the results, and print the min.
    // They'll all be the same, but this ensure's the function isn't optimized out.
    std::vector<int64_t> times;
    std::vector<T> results;
    for(int i = 0; i < runs; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        T result = func(path);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        times.push_back(duration.count());
        results.push_back(result);
    }
    int64_t fastest = *std::min_element(times.begin(), times.end());
    T lowest_result = *std::min(results.begin(), results.end());
    std::cout << "Timed result: " << lowest_result << ", best of " << runs << " runs: " << fastest << "us" << std::endl; 
}

#endif  // AOC22_AOC_H
