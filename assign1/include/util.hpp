#ifndef __UTIL_H__
#define __UTIL_H__

#include "../include/rank_support.hpp"
#include "../include/select_support.hpp"
#include "../include/sparse_array.hpp"

int generate_random_01(float oneFreq=0.5);
compact::vector<uint64_t, 1> generate_random_bit_vector(uint64_t size, float oneFreq=0.5);
sparse_array<string> generate_random_sparse_array(uint64_t size, float sparsity);

#endif /* __UTIL_H__ */
