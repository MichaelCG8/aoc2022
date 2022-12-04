#include <filesystem>
#include <fstream>
#include <iostream>

#include "lib.h"


#define WIN_POINTS (6)
#define DRAW_POINTS (3)
#define LOSS_POINTS (0)

int32_t part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    int32_t total = 0;
    while(std::getline(infile, line)) {
        const char *data = line.data();

        // Subtract the offset char and add 1, so that me contains the score given for that choice.
        const char them = data[0] - 'A' + 1;
        const char me = data[2] - 'X' + 1;
        bool draw = them == me;

        bool win = (me - them + 3) % 3 == 1;

        total += me + (win ? WIN_POINTS : (draw ? DRAW_POINTS : LOSS_POINTS));
    }
    return total;
}

int32_t part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto p = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(p) << std::endl;
    }
    int32_t total = 0;
    while(std::getline(infile, line)) {
        const char *data = line.data();

        // Subtract the offset char and add 1, so that them contains the score given for that choice.
        const char them = data[0] - 'A' + 1;
        const char instruction = data[2];
        bool win = instruction == 'Z';
        bool draw = instruction == 'Y';
        char me = draw ? them : (win ? (them + 1)%3 : (them + 2)%3);
        if(me == 0) {
            me = 3;
        }
        total += me + (win ? WIN_POINTS : (draw ? DRAW_POINTS : LOSS_POINTS));
    }
    return total;
}
