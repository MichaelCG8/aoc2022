#ifndef AOC22_AOC_H
#define AOC22_AOC_H

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#define quote(x) #x  // NOLINT(cppcoreguidelines-macro-usage)


template<typename T>
void time_execution(T (*func)(const char*), const char* path, int runs) {
    // Save all the results, and print the min.
    // They'll all be the same, but this ensure's the function isn't optimized out.
    std::vector<int64_t> times;
    std::vector<T> results;
    for(int i = 0; i < runs; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        T result = func(path);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        times.push_back(duration.count());
        results.push_back(result);
    }
    int64_t fastest = *std::min_element(times.begin(), times.end());
    T lowest_result = *std::min(results.begin(), results.end());
    std::cout << "Timed result: " << lowest_result << ", best of " << runs << " runs: " << fastest << "us" << std::endl; 
}


template<typename T, size_t MAX_SIZE>
 class AocArr { 
    private:
        size_t m_size {0};
        std::array<T, MAX_SIZE> m_array {};

    public:
        AocArr() = default;
        
        [[nodiscard]] size_t length() const { return m_size; }

        template<typename U, size_t MAX_SIZE_2> friend std::ostream& operator<< (std::ostream& out, const AocArr<U, MAX_SIZE_2>& aoc_arr);

        T& operator[] (size_t index);
        T* begin() { return m_array.begin(); }
        T* end() { return m_array.begin() + m_size; }
        void push(T value) { m_array[m_size++] = value; }
        T pop() { return m_array[--m_size]; }
}; 


template<typename U, size_t MAX_SIZE>
std::ostream& operator<< (std::ostream&out, const AocArr<U, MAX_SIZE>& aoc_arr)
{
    out << "AocArr<" << quote(T) << ", " << MAX_SIZE << ">(";
    for(size_t i = 0; i < aoc_arr.length(); i++) {
        if(i != 0) {
            out << ", ";
        }
        out << aoc_arr.m_array[i];
    }
    out << ")";

    return out;
}

template<typename T, size_t MAX_SIZE>
T& AocArr<T, MAX_SIZE>::operator[] (size_t index) {
    return m_array[index];
}

#endif  // AOC22_AOC_H
