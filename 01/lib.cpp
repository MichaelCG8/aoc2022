#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "lib.h"


long part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    long total = 0;
    long max = -1;
    auto emptyline = std::string("");
    while(std::getline(infile, line)) {
        if(line == emptyline) {
            max = total > max ? total : max;
            total = 0;
            continue;
        }
        total += std::stol(line);
    }
    max = total > max ? total : max;
    return max;
}

long part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    long total = 0;
    long max0 = -1;
    long max1 = -1;
    long max2 = -1;
    long *minmax = &max0;
    auto emptyline = std::string("");
    while(std::getline(infile, line)) {
        if(line == emptyline) {
            *minmax = total > *minmax ? total : *minmax;
            minmax = max0 < max1 ? &max0 : &max1;
            minmax = *minmax < max2 ? minmax : &max2;
            total = 0;
            continue;
        }
        total += std::stol(line);
    }
    *minmax = total > *minmax ? total : *minmax;
    return max0 + max1 + max2;
}
