#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "lib.h"


#define MAX_NODES (10'000)
#define DIRNAME_START (5)
#define CHILD_RESERVE_SIZE (1'000)
#define MAX_SMALL_DIR_SIZE (100'000)
#define TOTAL_SPACE (70'000'000)
#define REQUIRED_SPACE (30'000'000)


struct Node {  // NOLINT(altera-struct-pack-align)
    Node *parent;
    std::vector<Node*> children;
    uint64_t size;
    const std::string name;

    Node(Node *parent, uint64_t size, std::string name)
        : parent(parent)
        , size(size)
        , name(std::move(name))
    {}
};


inline Node* process_shell_command(std::string &line, Node *current_node, Node *root, std::vector<Node> &node_list) {
    if(line[2] == 'c') {
        auto dirname = line.substr(DIRNAME_START);
        if(dirname == "..") {
            return current_node->parent;
        }
        if(dirname == "/") {
            return root;
        }
        auto loc = std::find_if(
            current_node->children.begin(),
            current_node->children.end(),
            [&dirname](const Node *n) { return n->name == dirname;});
        if(loc != current_node->children.end()) {
            return (*loc);
        } 
        node_list.emplace_back(current_node, 0, dirname);
        current_node->children.push_back(&node_list.back());
        Node *next_node = current_node->children.back();
        next_node->children.reserve(CHILD_RESERVE_SIZE);
        return next_node;
    }
    // No action needed for ls.
    return current_node;
}


inline void process_file(std::string &line, Node *current_node, std::vector<Node> &node_list) {
    uint64_t size = 0;
    size_t char_pos = 0;
    for(auto c : line) {  // NOLINT(readability-identifier-length)
        char_pos++;
        if(c == ' ') {
            break;
        }
        size = size * 10 + (c - '0');  // NOLINT(*magic-numbers)
    }
    auto filename = line.substr(char_pos);
    auto loc = std::find_if(
        current_node->children.begin(),
        current_node->children.end(),
        [&filename](const Node *n) {return n->name == filename;});
    if(loc == current_node->children.end()) {
        node_list.emplace_back(current_node, size, filename);
        current_node->children.push_back(&node_list.back());
    }
}


uint64_t get_small_totals(const Node *current_node) {
    uint64_t total_small_dir_size = 0;
    auto child_idx_stack = std::vector<size_t>();
    size_t child_idx = 0;
    bool checked_children = false;
    while(true) {
        // Move to first child.
        if(!checked_children && !current_node->children.empty()) {
            current_node = current_node->children[0];  // NOLINT(readability-container-data-pointer)
            child_idx_stack.push_back(child_idx);
            child_idx = 0;
            continue;
        }
        // Check this node.
        if(!current_node->children.empty() && current_node->size < MAX_SMALL_DIR_SIZE) {
           total_small_dir_size += current_node->size; 
        }
        
        if(current_node->parent == nullptr) {
            break;
        }

        // Move to next sibling.
        child_idx++;
        if(child_idx < current_node->parent->children.size()) {
            checked_children = false;
            current_node->parent->size += current_node->size;
            current_node = current_node->parent->children[child_idx];
            continue;
        }
        
        // Move to parent.
        checked_children = true;
        current_node->parent->size += current_node->size;
        current_node = current_node->parent;
        child_idx = child_idx_stack.back();
        child_idx_stack.pop_back();
    }

    return total_small_dir_size;
}


uint64_t part1(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    auto node_list = std::vector<Node>();
    node_list.reserve(MAX_NODES);
    Node root = {nullptr, 0, "/"};
    Node *current_node = &root;
    current_node->children.reserve(CHILD_RESERVE_SIZE);
    while(std::getline(infile, line)) {
        switch(line[0]) {
            case '$':
                current_node = process_shell_command(line, current_node, &root, node_list);
                break;
            case 'd':
                // No action needed. We only have sizes to sum if we cd into them and see files.
                break;
            default:
                process_file(line, current_node, node_list);
                break;
        }
    }
    uint64_t total = get_small_totals(&root);
    return total;
}


inline void process_file_and_sum_size(std::string &line, Node *current_node, std::vector<Node> &node_list) {
    uint64_t size = 0;
    size_t char_pos = 0;
    for(auto c : line) {  // NOLINT(readability-identifier-length)
        char_pos++;
        if(c == ' ') {
            break;
        }
        size = size * 10 + (c - '0');  // NOLINT(*magic-numbers)
    }
    auto filename = line.substr(char_pos);
    auto loc = std::find_if(
        current_node->children.begin(),
        current_node->children.end(),
        [&filename](const Node *n) {return n->name == filename;});
    if(loc == current_node->children.end()) {
        node_list.emplace_back(current_node, size, filename);
        current_node->children.push_back(&node_list.back());
        Node *containing_dir = current_node;
        do {
            containing_dir->size += size;
            containing_dir = containing_dir->parent;
        } while(containing_dir != nullptr);
    }
}


uint64_t get_smallest_to_delete(const Node *current_node, uint64_t space_to_free) {
    uint64_t smallest_to_delete = TOTAL_SPACE;
    auto child_idx_stack = std::vector<size_t>();
    size_t child_idx = 0;
    bool checked_children = false;
    while(true) {
        // Move to first child.
        if(!checked_children && !current_node->children.empty()) {
            current_node = current_node->children[0];  // NOLINT(readability-container-data-pointer)
            child_idx_stack.push_back(child_idx);
            child_idx = 0;
            continue;
        }
        // Check this node.
        if(!current_node->children.empty() && current_node->size > space_to_free && current_node->size < smallest_to_delete) {
           smallest_to_delete = current_node->size; 
        }
        
        if(current_node->parent == nullptr) {
            break;
        }

        // Move to next sibling.
        child_idx++;
        if(child_idx < current_node->parent->children.size()) {
            checked_children = false;
            current_node = current_node->parent->children[child_idx];
            continue;
        }
        
        // Move to parent.
        checked_children = true;
        current_node = current_node->parent;
        child_idx = child_idx_stack.back();
        child_idx_stack.pop_back();
    }
    return smallest_to_delete;
}


uint64_t part2(const char* path) {
    std::string line;
    std::ifstream infile(path);
    if(!infile.is_open()) {
        auto fs_path = std::filesystem::path(path);
        std::cerr << "Couldn't open file: " << std::filesystem::absolute(fs_path) << std::endl;
    }
    auto node_list = std::vector<Node>();
    node_list.reserve(MAX_NODES);
    Node root = {nullptr, 0, "/"};
    Node *current_node = &root;
    current_node->children.reserve(CHILD_RESERVE_SIZE);
    while(std::getline(infile, line)) {
        switch(line[0]) {
            case '$':
                current_node = process_shell_command(line, current_node, &root, node_list);
                break;
            case 'd':
                // No action needed. We only have sizes to sum if we cd into them and see files.
                break;
            default:
                process_file_and_sum_size(line, current_node, node_list);
                break;
        }
    }
    uint64_t free_space = TOTAL_SPACE - root.size;
    uint64_t space_to_free = REQUIRED_SPACE - free_space;
    uint64_t smallest_to_delete = get_smallest_to_delete(&root, space_to_free);
    return smallest_to_delete;
}
