#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "lib.h"

#define CRT_LINE_LENGTH (40)
#define CRT_N_LINES (6)


int part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    int x = 1;  // NOLINT(readability-identifier-length)
    int cycle = 0;
    int sum_strength = 0;
    while(std::getline(infile, line)) {
        cycle++;
        if(cycle == 20 || (cycle - 20) % 40 == 0) {  // NOLINT(*magic-numbers)
            sum_strength += x * cycle;
        }

        if(line[0] == 'a') {
            cycle++;
            if(cycle == 20 || (cycle - 20) % 40 == 0) {  // NOLINT(*magic-numbers)
                sum_strength += x * cycle;
            }
            auto num_str = line.substr(5);  // NOLINT(*magic-numbers)
            int multiplier = 1;
            int addend = 0;
            for(auto c : num_str) {  // NOLINT(readability-identifier-length)
                if(c == '-') {
                    multiplier = -1;
                } else {
                    addend = addend * 10 + c - '0';  // NOLINT(*magic-numbers)
                }
            }
            addend *= multiplier;
            x += addend;
        }
    }
    return sum_strength;
}


std::string part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    int x = 1;  // NOLINT(readability-identifier-length)
    int cycle = 0;
    auto output = std::string(
        ".........." ".........." ".........." ".........." 
        ".........." ".........." ".........." ".........." 
        ".........." ".........." ".........." ".........." 
        ".........." ".........." ".........." ".........." 
        ".........." ".........." ".........." ".........." 
        ".........." ".........." ".........." ".........." 
    );
    while(std::getline(infile, line)) {
        if(cycle % CRT_LINE_LENGTH >= x - 1 && cycle % CRT_LINE_LENGTH<= x + 1) {
            output[cycle] = '#';
        }
        cycle++;
        if(line[0] == 'a') {
            if(cycle % CRT_LINE_LENGTH >= x - 1 && cycle % CRT_LINE_LENGTH <= x + 1) {
                output[cycle] = '#';
            }
            cycle++;
            auto num_str = line.substr(5);  // NOLINT(*magic-numbers)
            int multiplier = 1;
            int addend = 0;
            for(auto c : num_str) {  // NOLINT(readability-identifier-length)
                if(c == '-') {
                    multiplier = -1;
                } else {
                    addend = addend * 10 + c - '0';  // NOLINT(*magic-numbers)
                }
            }
            addend *= multiplier;
            x += addend;
        }
    }
    for(size_t i = 0; i < CRT_N_LINES; i++) {
        auto line = output.substr(i * CRT_LINE_LENGTH, CRT_LINE_LENGTH);
        std::cout << line << std::endl;
    }
    return output;
}
