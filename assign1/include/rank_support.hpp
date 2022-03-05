#include "../include/compact_vector.hpp"
#include <iostream>

class rank_support {
    compact::vector<unsigned, 1> *b = NULL;
    compact::vector<unsigned> *Rs = NULL;
    compact::vector<unsigned> *Rb = NULL;
    compact::vector<unsigned> *Rp = NULL;

public:
    rank_support(compact::vector<unsigned, 1> *b);
    int rank1();
};