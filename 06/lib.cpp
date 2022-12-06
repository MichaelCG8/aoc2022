#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "lib.h"

#define BUF_SIZE_PART_1 (4)
#define BUF_SIZE_PART_2 (14)


inline bool check_dup_part_1(const std::array<char, BUF_SIZE_PART_1> buffer) {
    return (
        buffer[0] == buffer[1]
        || buffer[0] == buffer[2]
        || buffer[0] == buffer[3]
        || buffer[1] == buffer[2]
        || buffer[1] == buffer[3]
        || buffer[2] == buffer[3]
    );
}

inline bool check_no_dup_part_2(const std::array<char, BUF_SIZE_PART_2> buffer) {
    for(size_t i = 0; i < BUF_SIZE_PART_2; i++) {
        for(size_t j = 0; j < i; j++) {
            if(buffer[i] == buffer[j]) {
                return false;
            }
        }
    }
    return true;
}


int part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    std::array<char, BUF_SIZE_PART_1> buffer;
    infile.get(buffer[0]);
    infile.get(buffer[1]);
    infile.get(buffer[2]);
    size_t buf_idx = BUF_SIZE_PART_1 - 1;
    int count = BUF_SIZE_PART_1 - 1;
    char c = 0;  // NOLINT(readability-identifier-length)
    while(infile >> std::noskipws >> c) {
        buffer[buf_idx] = c;
        buf_idx = (buf_idx + 1) % BUF_SIZE_PART_1;
        count++;
        if(!check_dup_part_1(buffer)) {
            return count;
        }
    }
    return -1;
}

int part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    std::array<char, BUF_SIZE_PART_2> buffer;
    for(size_t i = 0; i < BUF_SIZE_PART_2 - 1; i++) {
        infile.get(buffer[i]);
    }
    size_t buf_idx = BUF_SIZE_PART_2 - 1;
    int count = BUF_SIZE_PART_2 - 1;
    char c = 0;  // NOLINT(readability-identifier-length)
    while(infile >> std::noskipws >> c) {
        buffer[buf_idx] = c;
        buf_idx = (buf_idx + 1) % BUF_SIZE_PART_2;
        count++;
        if(check_no_dup_part_2(buffer)) {
            return count;
        }
    }
    return -1;
}
