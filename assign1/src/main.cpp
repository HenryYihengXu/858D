#include "../include/rank_support.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    unsigned n = atoi(argv[1]);
    compact::vector<unsigned, 1> b(n);
    rank_support r(&b);
    r.preExperiment();
}