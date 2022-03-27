#ifndef __RANK_SUPPORT_H__
#define __RANK_SUPPORT_H__

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
    bool needFreeB = false;
    compact::vector<uint64_t, 1> *b = NULL;
    compact::vector<uint64_t> *Rs = NULL;
    compact::vector<uint64_t> *Rb = NULL;

public:
    rank_support();
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

    uint64_t getBAt(uint64_t i);
    uint64_t getRsAt(uint64_t i);
    uint64_t getRbAt(uint64_t i);

    void setBAt(uint64_t i, uint64_t v);
    void setRsAt(uint64_t i, uint64_t v);
    void setRbAt(uint64_t i, uint64_t v);
};

#endif /* __RANK_SUPPORT_H__ */
