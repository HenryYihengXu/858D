#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>

#ifndef INCLUDE_UTIL
    #define INCLUDE_UTIL
    #include "../include/util.hpp"
#endif

using std::string;
using std::cout;
using std::endl;


int generate_random_01(float oneFreq) {
    float r = (float)(rand()) / (float)RAND_MAX;
    if (r > oneFreq) {
        return 0;
    } else {
        return 1;
    }
}

compact::vector<uint64_t, 1> generate_random_bit_vector(uint64_t size, float oneFreq) {
    compact::vector<uint64_t, 1> b(size);
    for (uint64_t i = 0; i < b.size(); i++) {
        b.at(i) = generate_random_01(oneFreq);
    }
    return b;
}

sparse_array<string> generate_random_sparse_array(uint64_t size, float sparsity) {
    compact::vector<uint64_t, 1> b = generate_random_bit_vector(size, 1 - sparsity);

    sparse_array<string> sa{};
    sa.create(size);

    uint64_t count = 0;
    for (uint64_t i = 0; i < b.size(); i++) {
        if (b.at(i) == 1) {
            count++;
            sa.append(std::to_string(count), i);
        }
    }

    return sa;
}
