#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "../include/suffix_array.hpp"

using namespace sdsl;
using std::string;
using std::cout;
using std::cerr;
using std::endl;

suffix_array::suffix_array() {}
suffix_array::~suffix_array() {}

suffix_array::suffix_array(string str)
    : n(str.length()), text(str), sa(n, 0, bits::hi(n)+1) 
{
    algorithm::calculate_sa(reinterpret_cast<const unsigned char*>(text.c_str()), text.length(), sa);
}

suffix_array::suffix_array(string str, uint64_t k)
    : n(str.length()), k(k), text(str), sa(n, 0, bits::hi(n)+1) 
{
    algorithm::calculate_sa(reinterpret_cast<const unsigned char*>(text.c_str()), text.length(), sa);
    
    string prevPrefix = "";
    int startPos = 0;
    for (uint64_t i = 0; i < n; i++) {
        int idx = sa[i];
        if (n - idx < k + 1) { // also count $
            if (!prevPrefix.empty()) {
                std::vector<uint64_t> interval;
                interval.push_back(startPos);
                interval.push_back(i - 1);
                prefTable.insert({prevPrefix, interval});
            }
            prevPrefix = "";
            continue;
        }
        
        string prefix = text.substr(idx, k);
        if (prevPrefix.empty()) {
            prevPrefix = prefix;
            startPos = i;
            continue;
        }

        if (prevPrefix.compare(prefix) != 0) {
            std::vector<uint64_t> interval;
            interval.push_back(startPos);
            interval.push_back(i - 1);
            prefTable.insert({prevPrefix, interval});
            
            prevPrefix = prefix;
            startPos = i;
        }
    }
    if (!prevPrefix.empty()) {
        std::vector<uint64_t> interval;
        interval.push_back(startPos);
        interval.push_back(n - 1);
        prefTable.insert({prevPrefix, interval});
    }
}

string suffix_array::to_string(bool printPrefTable) {
    std::stringstream result;
    result << endl;
    result << "Text: " << endl;
    result << text << endl;
    result << endl;

    result << "Length n = " << n << endl;
    result << endl;

    result << "Suffix array and correspoding suffixes: " << endl;
    int base = log10(n) / 1 + 1;

    for (uint64_t i = 0; i < n; i++) {
        result << std::setw(base) << i << ": " << std::setfill(' ') << std::setw(base) << sa[i] << "  " << text.substr(sa[i]) << endl;
    }
    result << endl;

    if (printPrefTable & (k != 0)) {
        result << "Prefix Table: " << endl;
        std::vector<string> keys;
        keys.reserve(prefTable.size());
        for (auto& it : prefTable) {
            keys.push_back(it.first);
        }
        std::sort (keys.begin(), keys.end());
        for(string it : keys) {
            std::vector<uint64_t> interval = prefTable[it];
            result << it << ": [" << interval[0] << ", " << interval[1] << "]" << endl;
        }
        result << endl;
    }

    return result.str();;
}
