#include "../include/compact_vector.hpp"
#ifndef INCLUDE_RANK_SUPPORT
    #define INCLUDE_RANK_SUPPORT
    #include "../include/rank_support.hpp"
#endif


class select_support {
    rank_support *r = NULL;
    uint64_t select1(uint64_t i, uint64_t l, uint64_t r);

public:
    select_support(rank_support *r);
    ~select_support();

    uint64_t select1(uint64_t i);
    uint64_t overhead();
    void save(string& fname);
    void save(std::ofstream& seqOut);
    void load(string& fname);
    void load(std::ifstream& seqIn);

    string to_string();
    /* Only for test purposes */
    uint64_t select1ByCount(uint64_t i);
};
