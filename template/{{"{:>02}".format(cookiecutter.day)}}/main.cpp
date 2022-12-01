#include <iostream>

#include "../aoc.h"
#include "lib.h"


int main() {
    auto result1 = part1("{{"{:>02}".format(cookiecutter.day)}}/input");
    std::cout << "Part 1: " << result1 << std::endl;
    time(&part1, "{{"{:>02}".format(cookiecutter.day)}}/input", 1000);
    
    auto result2 = part2("{{"{:>02}".format(cookiecutter.day)}}/input");
    std::cout << "Part 2: " << result2 << std::endl;
    time(&part2, "{{"{:>02}".format(cookiecutter.day)}}/input", 1000);
    
    return 0;
}
