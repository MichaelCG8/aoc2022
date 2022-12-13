#ifndef AOC22_11_LIB_H
#define AOC22_11_LIB_H

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

#include "../aoc.h"

#define N_ROUNDS_1 (20)
#define N_ROUNDS_2 (10'000)
#define WORRY_DIVISOR (3)


enum LINE_INDEXES {
    LINE_MONKEY_ID_IDX = 0,
    LINE_STARTING_LEVELS_IDX = 2,
    LINE_OPERATION_IDX = 2,
    LINE_TEST_IDX = 2,
    LINE_TRUE_DEST_IDX = 7,

    MONKEY_ID_IDX = 7,
    ITEMS_START = 18,
    OPERATION_TYPE_IDX = 23,
    OPERATION_VAL_START = 25,
    TEST_DIVISOR_START = 21,
    TRUE_DEST_IDX = 29,
    FALSE_DEST_IDX = 30,
};


class Monkey {
    public:
        std::vector<uint64_t> worry_levels;
        size_t true_destination {0};
        size_t false_destination {0};
        std::function<uint64_t(uint64_t)> operation;
        std::function<bool(uint64_t)> test;
        uint64_t n_inspections {0};
        
        Monkey()
            : operation([](uint64_t worry_level) { return worry_level; })
            , test([](uint64_t worry_level) { return true; })  // NOLINT(misc-unused-parameters)
            {}
};

template<size_t N_MONKEYS>
uint64_t part1(const char* path) {
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
        if(line[LINE_MONKEY_ID_IDX] == 'M') {
            monkey_id = line[MONKEY_ID_IDX] - '0';
        } else if(line[LINE_STARTING_LEVELS_IDX] == 'S') {
            auto items_string = line.substr(ITEMS_START);
            uint64_t worry_level = 0;
            for(auto c : items_string) {  // NOLINT(readability-identifier-length)
                if(c == ',') {
                    monkeys[monkey_id].worry_levels.push_back(worry_level);
                    worry_level = 0;
                } else if(c == ' ') {
                    continue;
                } else {
                    worry_level = worry_level * 10 + c - '0';  // NOLINT(*magic-numbers)
                }
            }
            monkeys[monkey_id].worry_levels.push_back(worry_level);
        } else if(line[LINE_OPERATION_IDX] == 'O') {
            auto operation_type = line[OPERATION_TYPE_IDX];
            auto operation_value_string = line.substr(OPERATION_VAL_START);
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
                for(auto c : operation_value_string) {  // NOLINT(readability-identifier-length)
                    operation_value = operation_value * 10 + c - '0';  // NOLINT(*magic-numbers)
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
        } else if(line[LINE_TEST_IDX] == 'T') {
            auto divisor_string = line.substr(TEST_DIVISOR_START);
            uint64_t divisor = 0;
            for(auto c : divisor_string) {  // NOLINT(readability-identifier-length)
                divisor = divisor * 10 + c - '0';  // NOLINT(*magic-numbers)
            }
            monkeys[monkey_id].test = std::function {
                [divisor](uint64_t worry_level) {
                    return worry_level % divisor == 0;
                }
            };
        } else if(line[LINE_TRUE_DEST_IDX] == 't') {
            monkeys[monkey_id].true_destination = line[TRUE_DEST_IDX] - '0';
        } else {
            monkeys[monkey_id].false_destination = line[FALSE_DEST_IDX] - '0';
        }
    }
    for(int round = 0; round < N_ROUNDS_1; round++) {
        for(size_t i = 0; i < N_MONKEYS; i++) {
            auto monkey = &(monkeys[i]);
            monkey->n_inspections += monkey->worry_levels.size();
            for(auto level : monkey->worry_levels) {
                auto new_level = monkey->operation(level) / WORRY_DIVISOR;
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
        if(line[LINE_MONKEY_ID_IDX] == 'M') {
            monkey_id = line[MONKEY_ID_IDX] - '0';
        } else if(line[LINE_STARTING_LEVELS_IDX] == 'S') {
            auto items_string = line.substr(ITEMS_START);
            uint64_t worry_level = 0;
            for(auto c : items_string) {  // NOLINT(readability-identifier-length)
                if(c == ',') {
                    monkeys[monkey_id].worry_levels.push_back(worry_level);
                    worry_level = 0;
                } else if(c == ' ') {
                    continue;
                } else {
                    worry_level = worry_level * 10 + c - '0';  // NOLINT(*magic-numbers)
                }
            }
            monkeys[monkey_id].worry_levels.push_back(worry_level);
        } else if(line[LINE_OPERATION_IDX] == 'O') {
            auto operation_type = line[OPERATION_TYPE_IDX];
            auto operation_value_string = line.substr(OPERATION_VAL_START);
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
                for(auto c : operation_value_string) {  // NOLINT(readability-identifier-length)
                    operation_value = operation_value * 10 + c - '0';  // NOLINT(*magic-numbers)
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
        } else if(line[LINE_TEST_IDX] == 'T') {
            auto divisor_string = line.substr(TEST_DIVISOR_START);
            uint64_t divisor = 0;
            for(auto c : divisor_string) {  // NOLINT(readability-identifier-length)
                divisor = divisor * 10 + c - '0';  // NOLINT(*magic-numbers)
            }
            common_test_divisor *= divisor;
            monkeys[monkey_id].test = std::function {
                [divisor](uint64_t worry_level) {
                    return worry_level % divisor == 0;
                }
            };
        } else if(line[LINE_TRUE_DEST_IDX] == 't') {
            monkeys[monkey_id].true_destination = line[TRUE_DEST_IDX] - '0';
        } else {
            monkeys[monkey_id].false_destination = line[FALSE_DEST_IDX] - '0';
        }
    }
    for(int round = 0; round < N_ROUNDS_2; round++) {
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
