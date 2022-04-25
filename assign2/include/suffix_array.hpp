#ifndef __SUFFIX_ARRAY_H__
#define __SUFFIX_ARRAY_H__

#include <sdsl/suffix_arrays.hpp>
#include <vector>
#include <string>

using namespace sdsl;
using std::string;

class suffix_array {
    uint64_t n = 0;
    uint64_t k = 0;
    string text = "";
    int_vector<64> sa;
    std::unordered_map<string, std::vector<uint64_t>> prefTable;

public:
    suffix_array();
    ~suffix_array();
    suffix_array(string text);
    suffix_array(string text, uint64_t k);
    
    string to_string(bool printPrefTable=true);
};

#endif /* __SUFFIX_ARRAY_H__ */
