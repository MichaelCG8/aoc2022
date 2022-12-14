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

void print_stacks(const std::array<std::array<char, N_CRATES>, N_STACKS> &stacks, const std::array<size_t, N_STACKS> &count) {
    for(size_t i = 0; i < N_STACKS; i++) {
        for(size_t j = 0; j < count[i]; j++) {
            std::cout << stacks[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void read_initial(std::array<std::array<char, N_CRATES>, N_STACKS> &stacks, std::array<size_t, N_STACKS> &count, std::istream& infile) {
    std::string line;
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
            char c = line[4 * i + 1];  // NOLINT(readability-identifier-length)
            if(c == ' ') {
                continue;
            }
            stacks[i][N_CRATES - count[i] - 1] = c;
            count[i] += 1;
        }
    }
}


std::string part1(const char* path) {
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    std::array<std::array<char, N_CRATES>, N_STACKS> stacks = {};
    std::array<size_t, N_STACKS> count = {
#ifndef TESTING
        0, 0, 0, 0, 0, 0,
#endif
        0, 0, 0};

    read_initial(stacks, count, infile);
        
    std::string line;
    std::getline(infile, line);  // Skip blank line.

    std::regex regex(R"(^move (\d+) from (\d+) to (\d+)$)");
    std::smatch matches;
#ifdef TESTING
    print_stacks(stacks, count);
#endif
    while(std::getline(infile, line)) {
        std::regex_match(line, matches, regex);
        int move = std::stoi(matches[1].str());
        int from = std::stoi(matches[2].str()) - 1;
        int to = std::stoi(matches[3].str()) - 1;  // NOLINT(readability-identifier-length)
        for(int i = 0; i < move; i++) {
            stacks[to][count[to]] = stacks[from][count[from] - 1];
            count[to]++;
            count[from]--;
        }
#ifdef TESTING
        print_stacks(stacks, count);
#endif
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
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    std::array<std::array<char, N_CRATES>, N_STACKS> stacks = {};
    std::array<size_t, N_STACKS> count = {
#ifndef TESTING
        0, 0, 0, 0, 0, 0,
#endif
        0, 0, 0};

    read_initial(stacks, count, infile);

    std::getline(infile, line);  // Skip blank line.

    std::regex regex(R"(^move (\d+) from (\d+) to (\d+)$)");
    std::smatch matches;
#ifdef TESTING
    print_stacks(stacks, count);
#endif
    while(std::getline(infile, line)) {
        std::regex_match(line, matches, regex);
        int move = std::stoi(matches[1].str());
        int from = std::stoi(matches[2].str()) - 1;
        int to = std::stoi(matches[3].str()) - 1;  // NOLINT(readability-identifier-length)
        for(int i = 0; i < move; i++) {
            stacks[to][count[to]] = stacks[from][count[from] - move + i];
            count[to]++;
        }
        count[from] -= move;
#ifdef TESTING
        print_stacks(stacks, count);
#endif
    }
    std::string result = std::string();
    for(int i = 0; i < N_STACKS; i++) {
        result += stacks[i][count[i] - 1];
    }
    return result;
}
