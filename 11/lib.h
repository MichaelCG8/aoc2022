#ifndef AOC22_11_LIB_H
#define AOC22_11_LIB_H

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

#include "../aoc.h"


class Monkey {
    public:
        std::vector<uint64_t> worry_levels;
        size_t true_destination;
        size_t false_destination;
        std::function<uint64_t(uint64_t)> operation;
        std::function<bool(uint64_t)> test;
        uint64_t n_inspections;
        
        Monkey()
            : worry_levels(std::vector<uint64_t>())
            , true_destination(0)
            , false_destination(0)
            , operation([](uint64_t worry_level) { return worry_level; })
            , test([](uint64_t worry_level) { return true; })
            , n_inspections(0)
            {}
};

template<size_t N_MONKEYS>
int part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }

    auto monkeys = AocArr<Monkey, N_MONKEYS>();
    for(size_t i = 0; i < N_MONKEYS; i++) {
        monkeys.push(Monkey());
    }
    size_t monkey_id = 0;
    while(std::getline(infile, line)) {
        if(line.length() == 0) {
            continue;
        }
        if(line[0] == 'M') {
            monkey_id = line[7] - '0';
        } else if(line[2] == 'S') {
            auto items_string = line.substr(18);
            uint64_t worry_level = 0;
            for(auto c : items_string) {
                if(c == ',') {
                    monkeys[monkey_id].worry_levels.push_back(worry_level);
                    worry_level = 0;
                } else if(c == ' ') {
                    continue;
                } else {
                    worry_level = worry_level * 10 + c - '0';
                }
            }
            monkeys[monkey_id].worry_levels.push_back(worry_level);
        } else if(line[2] == 'O') {
            auto operation_type = line[23];
            auto operation_value_string = line.substr(25);
            if(operation_value_string[0] == 'o') {
                if(operation_type == '*') {
                    monkeys[monkey_id].operation = std::function {
                        [](uint64_t worry_level) {
                            return worry_level * worry_level;
                        }
                    };
                } else {
                    monkeys[monkey_id].operation = std::function {
                        [](uint64_t worry_level) {
                            return worry_level + worry_level;
                        }
                    };
                }
            } else {
                uint64_t operation_value = 0;
                for(auto c : operation_value_string) {
                    operation_value = operation_value * 10 + c - '0';
                }
                if(operation_type == '*') {
                    monkeys[monkey_id].operation = std::function {
                        [operation_value](uint64_t worry_level) {
                            return worry_level * operation_value;
                        }
                    };
                } else {
                    monkeys[monkey_id].operation = std::function {
                        [operation_value](uint64_t worry_level) {
                            return worry_level + operation_value;
                        }
                    };
                }
            }
        } else if(line[2] == 'T') {
            auto divisor_string = line.substr(21);
            uint64_t divisor = 0;
            for(auto c : divisor_string) {
                divisor = divisor * 10 + c - '0';
            }
            monkeys[monkey_id].test = std::function {
                [divisor](uint64_t worry_level) {
                    return worry_level % divisor == 0;
                }
            };
        } else if(line[7] == 't') {
            monkeys[monkey_id].true_destination = line[29] - '0';
        } else {
            monkeys[monkey_id].false_destination = line[30] - '0';
        }
    }
    for(int round = 0; round < 20; round++) {
        for(size_t i = 0; i < N_MONKEYS; i++) {
            auto monkey = &(monkeys[i]);
            monkey->n_inspections += monkey->worry_levels.size();
            for(auto level : monkey->worry_levels) {
                auto new_level = monkey->operation(level) / 3;
                auto destination = monkey->test(new_level) ? monkey->true_destination : monkey->false_destination;
                monkeys[destination].worry_levels.push_back(new_level);    
            }
            monkey->worry_levels.clear();
        }
    }

    uint64_t max0 = 0;
    uint64_t max1 = 0;
    uint64_t *pLowestMax = &max0;
    for(auto monkey : monkeys) {
        if(monkey.n_inspections > *pLowestMax) {
            *pLowestMax = monkey.n_inspections;
            pLowestMax = max0 < max1 ? &max0 : &max1;
        }
    }
    return max0 * max1;
}

template<size_t N_MONKEYS>
uint64_t part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }

    auto monkeys = AocArr<Monkey, N_MONKEYS>();
    for(size_t i = 0; i < N_MONKEYS; i++) {
        monkeys.push(Monkey());
    }
    size_t monkey_id = 0;
    uint64_t common_test_divisor = 1;
    while(std::getline(infile, line)) {
        if(line.length() == 0) {
            continue;
        }
        if(line[0] == 'M') {
            monkey_id = line[7] - '0';
        } else if(line[2] == 'S') {
            auto items_string = line.substr(18);
            uint64_t worry_level = 0;
            for(auto c : items_string) {
                if(c == ',') {
                    monkeys[monkey_id].worry_levels.push_back(worry_level);
                    worry_level = 0;
                } else if(c == ' ') {
                    continue;
                } else {
                    worry_level = worry_level * 10 + c - '0';
                }
            }
            monkeys[monkey_id].worry_levels.push_back(worry_level);
        } else if(line[2] == 'O') {
            auto operation_type = line[23];
            auto operation_value_string = line.substr(25);
            if(operation_value_string[0] == 'o') {
                if(operation_type == '*') {
                    monkeys[monkey_id].operation = std::function {
                        [](uint64_t worry_level) {
                            return worry_level * worry_level;
                        }
                    };
                } else {
                    monkeys[monkey_id].operation = std::function {
                        [](uint64_t worry_level) {
                            return worry_level + worry_level;
                        }
                    };
                }
            } else {
                uint64_t operation_value = 0;
                for(auto c : operation_value_string) {
                    operation_value = operation_value * 10 + c - '0';
                }
                if(operation_type == '*') {
                    monkeys[monkey_id].operation = std::function {
                        [operation_value](uint64_t worry_level) {
                            return worry_level * operation_value;
                        }
                    };
                } else {
                    monkeys[monkey_id].operation = std::function {
                        [operation_value](uint64_t worry_level) {
                            return worry_level + operation_value;
                        }
                    };
                }
            }
        } else if(line[2] == 'T') {
            auto divisor_string = line.substr(21);
            uint64_t divisor = 0;
            for(auto c : divisor_string) {
                divisor = divisor * 10 + c - '0';
            }
            common_test_divisor *= divisor;
            monkeys[monkey_id].test = std::function {
                [divisor](uint64_t worry_level) {
                    return worry_level % divisor == 0;
                }
            };
        } else if(line[7] == 't') {
            monkeys[monkey_id].true_destination = line[29] - '0';
        } else {
            monkeys[monkey_id].false_destination = line[30] - '0';
        }
    }
    for(int round = 0; round < 10000; round++) {
        for(size_t i = 0; i < N_MONKEYS; i++) {
            auto monkey = &(monkeys[i]);
            monkey->n_inspections += monkey->worry_levels.size();
            for(auto level : monkey->worry_levels) {
                auto new_level = monkey->operation(level) % common_test_divisor;
                auto destination = monkey->test(new_level) ? monkey->true_destination : monkey->false_destination;
                monkeys[destination].worry_levels.push_back(new_level);
            }
            monkey->worry_levels.clear();
        }
    }

    uint64_t max0 = 0;
    uint64_t max1 = 0;
    uint64_t *pLowestMax = &max0;
    for(auto monkey : monkeys) {
        if(monkey.n_inspections > *pLowestMax) {
            *pLowestMax = monkey.n_inspections;
            pLowestMax = max0 < max1 ? &max0 : &max1;
        }
    }
    return max0 * max1;
}


#endif  // AOC22_11_LIB_H
