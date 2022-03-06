#include "../include/compact_vector.hpp"

class rank_support {
    unsigned n = 0;
    unsigned RbCovers = 0;
    unsigned RsCovers = 0;
    unsigned RbSize = 0;
    unsigned RsSize = 0;
    unsigned RbBits = 0;
    unsigned RsBits = 0;
    compact::vector<unsigned, 1> *b = NULL;
    compact::vector<unsigned> *Rs = NULL;
    compact::vector<unsigned> *Rb = NULL;

public:
    rank_support(compact::vector<unsigned, 1> *b);
    unsigned countRank1(unsigned idx);
    std::string to_string();
    unsigned popcount(unsigned idx);
    unsigned rank1(unsigned idx);
    void preExperiment();
};