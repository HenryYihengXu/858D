#ifndef INCLUDE_RANK_SUPPORT
    #define INCLUDE_RANK_SUPPORT
    #include "../include/rank_support.hpp"
#endif

#ifndef INCLUDE_SELECT_SUPPORT
    #define INCLUDE_SELECT_SUPPORT
    #include "../include/select_support.hpp"
#endif

#ifndef INCLUDE_SPARSE_ARRAY
    #define INCLUDE_SPARSE_ARRAY
    #include "../include/sparse_array.hpp"
#endif

int generate_random_01(float oneFreq=0.5);
compact::vector<uint64_t, 1> generate_random_bit_vector(uint64_t size, float oneFreq=0.5);
sparse_array<string> generate_random_sparse_array(uint64_t size, float sparsity);
