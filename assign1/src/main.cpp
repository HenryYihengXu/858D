#include "../include/rank_support.hpp"
#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>

void test_rank_support_structure(unsigned size, float oneFreq=0.5);
int generate_random_01(float oneFreq=0.5);
compact::vector<unsigned, 1> generate_random_bit_vector(unsigned size, float oneFreq=0.5);

int main(int argc, char* argv[]) {
    unsigned n = atoi(argv[1]);
    float oneFreq = atof(argv[2]);
    srand(time(NULL));
    compact::vector<unsigned, 1> b = generate_random_bit_vector(n, oneFreq);
    rank_support r(&b);
    std::cout << r.to_string();
}

int generate_random_01(float oneFreq) {
    float r = (float)(rand()) / (float)RAND_MAX;
    if (r > oneFreq) {
        return 0;
    } else {
        return 1;
    }
}

compact::vector<unsigned, 1> generate_random_bit_vector(unsigned size, float oneFreq) {
    compact::vector<unsigned, 1> b(size);
    for (unsigned i = 0; i < b.size(); i++) {
        b.at(i) = generate_random_01(oneFreq);
    }
    return b;
}

