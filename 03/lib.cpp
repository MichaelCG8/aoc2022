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
        uint64_t first = 0;
        uint64_t second = 0;
        // Set a bit for each letter. A-Z and a-z covers a range smaller than 64.
        for(size_t i = 0; i < line.length() / 2; i++) {
            char flag_pos = line[i] - 'A';
            first |= (1ll << flag_pos);
        }
        for(size_t i = line.length() / 2; i < line.length(); i++) {
            char flag_pos = line[i] - 'A';
            second |= (1ll << flag_pos);
        }
        // Anding the two values finds the common part.
        uint64_t unique = first & second;
        char first_set = 0;
        // Find the only set bit. There are faster ways e.g. ffs() or bit manipulation smartness but this will do.
        for(char i = 0; i < 64; i++) {
            if((unique >> i) & 1) {
                first_set = i;
                break;
            }
        }
        total += first_set + 'A' <= 'Z' ? first_set + 27 : first_set + 'A' - 'a' + 1;
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
    uint64_t flags[3] = {0, 0, 0};
    int position = -1;
    while(std::getline(infile, line)) {
        position += 1;
        if(position == 3) {
            position = 0;
            uint64_t unique = flags[0] & flags[1] & flags[2];
            flags[0] = 0;
            flags[1] = 0;
            flags[2] = 0;
            char first_set = 0;
            for(char i = 0; i < 64; i++) {
                if((unique >> i) & 1) {
                    first_set = i;
                    break;
                }
            }
            total += first_set + 'A' <= 'Z' ? first_set + 27 : first_set + 'A' - 'a' + 1;
        }
        for(size_t i = 0; i < line.length(); i++) {
            char flag_pos = line[i] - 'A';
            flags[position] |= (1ll << flag_pos);
        }
    }
    uint64_t unique = flags[0] & flags[1] & flags[2];
    char first_set = 0;
    for(char i = 0; i < 64; i++) {
        if((unique >> i) & 1) {
            first_set = i;
            break;
        }
    }
    total += first_set + 'A' <= 'Z' ? first_set + 27 : first_set + 'A' - 'a' + 1;
    return total;
}
