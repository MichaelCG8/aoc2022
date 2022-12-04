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
    while(std::getline(infile, line)) {
    }
    return 0;
}

int part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    while(std::getline(infile, line)) {
    }
    return 0;
}
