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

    uint64_t naiveFindLeftBound(string pattern, uint64_t left, uint64_t right);
    uint64_t naiveFindRightBound(string pattern, uint64_t left, uint64_t right);
    uint64_t simpAccelFindLeftBound(string pattern, uint64_t left, uint64_t right, int64_t lcpLeft, int64_t lcpRight);
    uint64_t simpAccelFindRightBound(string pattern, uint64_t left, uint64_t right, int64_t lcpLeft, int64_t lcpRight);

public:
    suffix_array();
    ~suffix_array();
    suffix_array(string text);
    suffix_array(string text, uint64_t k);
    
    std::vector<uint64_t> query(string pattern, string mode);
    std::vector<uint64_t> naiveQuery(string pattern);
    std::vector<uint64_t> simpAccelQuery(string pattern);
    string getText(uint64_t start, uint64_t len);

    string to_string(bool printPrefTable=true);
};

#endif /* __SUFFIX_ARRAY_H__ */
