#include "../include/compact_vector.hpp"
#include "../include/rank_support.hpp"

class select_support {
    rank_support *r = NULL;
    uint64_t select1(uint64_t i, uint64_t l, uint64_t r);

public:
    select_support(rank_support *r);
    uint64_t select1(uint64_t i);
    uint64_t overhead();
    void save(string& fname);
    void load(string& fname);

    /* Only for test purposes */
    uint64_t select1ByCount(uint64_t i);
};
