#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include "lib.h"


#ifdef TESTING
#define N_STACKS (3)
#define N_CRATES (6)
#else
#define N_STACKS (9)
#define N_CRATES (56)
#endif

void print_stacks(std::array<std::array<char, N_CRATES>, N_STACKS> stacks, std::array<size_t, N_STACKS> count) {
    for(size_t i = 0; i < N_STACKS; i++) {
        for(size_t j = 0; j < count[i]; j++) {
            std::cout << stacks[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


std::string part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    std::array<std::array<char, N_CRATES>, N_STACKS> stacks = {};
    std::array<size_t, N_STACKS> count = {
#ifndef TESTING
        0, 0, 0, 0, 0, 0,
#endif
        0, 0, 0};

    while(std::getline(infile, line)) {
        // End of setup.
        if(line[1] == '1') {
            // Each stack is only valid from N_CRATES - count[i] onwards.
            // Shuffle them all down.
            for(size_t i = 0; i < N_STACKS; i++) {
                for(size_t j = 0; j < count[i]; j++) {
                    stacks[i][j] = stacks[i][N_CRATES - count[i] + j];
                }
            }
            break;
        }
        // Stack crates from end of array towards start.
        for(size_t i = 0; i < N_STACKS; i++) {
            char c = line[4 * i + 1];
            if(c == ' ') {
                continue;
            }
            stacks[i][N_CRATES - count[i] - 1] = c;
            count[i] += 1;
        }
    }
        
    std::getline(infile, line);  // Skip blank line.

    std::regex regex(R"(^move (\d+) from (\d+) to (\d+)$)");
    std::smatch m;
    // print_stacks(stacks, count);
    while(std::getline(infile, line)) {
        std::regex_match(line, m, regex);
        int move = std::stoi(m[1].str());
        int from = std::stoi(m[2].str()) - 1;
        int to = std::stoi(m[3].str()) - 1;
        for(int i = 0; i < move; i++) {
            stacks[to][count[to]] = stacks[from][count[from] - 1];
            count[to]++;
            count[from]--;
        }
        // print_stacks(stacks, count);
    }
    std::string result = std::string();
    for(int i = 0; i < N_STACKS; i++) {
        result += stacks[i][count[i] - 1];
    }
    return result;
}


std::string part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    std::array<std::array<char, N_CRATES>, N_STACKS> stacks = {};
    std::array<size_t, N_STACKS> count = {
#ifndef TESTING
        0, 0, 0, 0, 0, 0,
#endif
        0, 0, 0};

    while(std::getline(infile, line)) {
        // End of setup.
        if(line[1] == '1') {
            // Each stack is only valid from N_CRATES - count[i] onwards.
            // Shuffle them all down.

            for(size_t i = 0; i < N_STACKS; i++) {
                for(size_t j = 0; j < count[i]; j++) {
                    stacks[i][j] = stacks[i][N_CRATES - count[i] + j];
                }
            }
            break;
        }
        // Stack crates from end of array towards start.
        for(size_t i = 0; i < N_STACKS; i++) {
            char c = line[4 * i + 1];
            if(c == ' ') {
                continue;
            }
            stacks[i][N_CRATES - count[i] - 1] = c;
            count[i] += 1;
        }
    }
        
    std::getline(infile, line);  // Skip blank line.

    std::regex regex(R"(^move (\d+) from (\d+) to (\d+)$)");
    std::smatch m;
    // print_stacks(stacks, count);
    while(std::getline(infile, line)) {
        std::regex_match(line, m, regex);
        int move = std::stoi(m[1].str());
        int from = std::stoi(m[2].str()) - 1;
        int to = std::stoi(m[3].str()) - 1;
        for(int i = 0; i < move; i++) {
            stacks[to][count[to]] = stacks[from][count[from] - move + i];
            count[to]++;
        }
        count[from] -= move;
        // print_stacks(stacks, count);
    }
    std::string result = std::string();
    for(int i = 0; i < N_STACKS; i++) {
        result += stacks[i][count[i] - 1];
    }
    return result;
}
