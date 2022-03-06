#include "../include/compact_vector.hpp"
using std::string;

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
    uint64_t rank1(uint64_t i);
    uint64_t overhead();
    void save(string& fname);
    void load(string& fname);
    
    unsigned popcount(unsigned idx);
    string to_string();
    uint64_t rank1ByCount(uint64_t idx);
    void preExperiment();
};