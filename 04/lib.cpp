#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "lib.h"


int part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    int total = 0;
    while(std::getline(infile, line)) {
        // range will contain low0, high0, low1, high1.
        int range[4] = {0, 0, 0, 0};
        size_t range_idx = 0;
        for(size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if(c == '-' || c == ',') {
                range_idx += 1;
            } else {
                char digit = c - '0';
                range[range_idx] = range[range_idx] * 10 + digit;
            }
        }
        // If either the low or high endpoints match, one must include the other.
        // Otherwise, check if one completely encloses the other.
        if(
            range[0] == range[2]
            || range[1] == range[3]
            || (range[0] < range[2] && range[1] > range[3])
            || (range[0] > range[2] && range[1] < range[3])
        ) {
            total += 1;
        }
    }
    return total;
}

int part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    int total = 0;
    while(std::getline(infile, line)) {
        // range will contain low0, high0, low1, high1.
        int range[4] = {0, 0, 0, 0};
        size_t range_idx = 0;
        for(size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if(c == '-' || c == ',') {
                range_idx += 1;
            } else {
                char digit = c - '0';
                range[range_idx] = range[range_idx] * 10 + digit;
            }
        }
        // If either the low or high endpoints match, one must include the other.
        // Otherwise, check if one partially encloses the other.
        if(
            range[0] == range[2]
            || range[1] == range[3]
            || (range[0] < range[2] && range[1] >= range[2])
            || (range[0] > range[2] && range[0] <= range[3])
        ) {
            total += 1;
        }
    }
    return total;
}
