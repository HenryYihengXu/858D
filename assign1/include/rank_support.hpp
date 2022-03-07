#include "../include/compact_vector.hpp"
using std::string;

class rank_support {
    uint64_t n = 0;
    uint64_t RbCovers = 0;
    uint64_t RsCovers = 0;
    uint64_t RbSize = 0;
    uint64_t RsSize = 0;
    uint64_t RbBits = 0;
    uint64_t RsBits = 0;
    compact::vector<uint64_t, 1> *b = NULL;
    compact::vector<uint64_t> *Rs = NULL;
    compact::vector<uint64_t> *Rb = NULL;

public:
    rank_support(compact::vector<uint64_t, 1> *b);
    ~rank_support();
    
    uint64_t rank1(uint64_t i);
    uint64_t overhead();
    void save(string& fname);
    void save(std::ofstream& seqOut);
    void load(string& fname);
    void load(std::ifstream& seqIn);

    uint64_t popcount(uint64_t idx);
    string to_string();
    /* Only for test purposes */
    uint64_t rank1ByCount(uint64_t idx);

    uint64_t getN();
    uint64_t getRsCovers();
    uint64_t getRbCovers();
    uint64_t getRsSize();
    uint64_t getRbSize();
    uint64_t getRsBits();
    uint64_t getRbBits();

    uint64_t bAt(uint64_t i);
    uint64_t RsAt(uint64_t i);
    uint64_t RbAt(uint64_t i);

    void preExperiment();
};
