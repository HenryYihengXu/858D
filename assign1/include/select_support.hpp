#include "../include/compact_vector.hpp"
#include "../include/rank_support.hpp"

class select_support {
    rank_support *r = NULL;

public:
    select_support(rank_support *r);
    uint64_t select1(uint64_t i);
    uint64_t overhead();
    void save(string& fname);
    void load(string& fname);
};
