#include "../include/compact_vector.hpp"

class rank_support {
    compact::vector<unsigned, 1> *b = NULL;
    compact::vector<unsigned> *Rs = NULL;
    compact::vector<unsigned> *Rb = NULL;

public:
    rank_support(compact::vector<unsigned, 1> *b);
    std::string to_string();
    int rank1(unsigned idx);
    void preExperiment();
};