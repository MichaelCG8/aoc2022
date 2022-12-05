#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "lib.h"


int part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    while(std::getline(infile, line)) {
    }
    return 0;
}

int part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    while(std::getline(infile, line)) {
    }
    return 0;
}
