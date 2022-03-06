#include "../include/rank_support.hpp"
#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>

using std::string;
using std::cout;
using std::endl;

void test_rank1(unsigned num_test=10);
int generate_random_01(float oneFreq=0.5);
compact::vector<unsigned, 1> generate_random_bit_vector(unsigned size, float oneFreq=0.5);

int main(int argc, char* argv[]) {
    // unsigned n = atoi(argv[1]);
    // float oneFreq = atof(argv[2]);
    srand(time(NULL));
    test_rank1();
}

void test_rank1(unsigned num_test) {
    unsigned passed = 0;
    for (unsigned i = 0; i < num_test; i++) {
        unsigned n = 16 + rand() % 64;
        float oneFreq = (float)(rand()) / (float)RAND_MAX;
        compact::vector<unsigned, 1> b = generate_random_bit_vector(n, oneFreq);
        rank_support r(&b);

        unsigned idx = rand() % n;
        unsigned rank1 = r.rank1(idx);
        unsigned rank1ByCount = r.countRank1(idx);
        cout << "Test " << i << ": size = " << n << ", one frequency = " << oneFreq << 
            ", index = " << idx << ", rank 1 = " << rank1 << ", rank 1 by count = " << rank1ByCount << endl;
        // cout << r.to_string();
        if (rank1 == rank1ByCount) {
            cout << "passed\n";
            passed++;
        } else {
            cout << "failed\n";
        }
        cout << "\n";
    }

    if (passed == num_test) {
        cout << "ALL TESTS PASSED\n";
    } else {
        cout << "SOME TESTS FAILED\n";
    }
    cout << "\n";
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

