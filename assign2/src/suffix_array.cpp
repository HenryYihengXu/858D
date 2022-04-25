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

std::vector<uint64_t> suffix_array::naiveQuery(string pattern) {
    std::vector<uint64_t> result;
    uint64_t left = 0;
    uint64_t right = n - 1;
    if (k != 0) {
        string prefix = pattern.substr(0, k);
        if (prefTable.find(prefix) == prefTable.end()) {
            result.push_back(0);
            return result;
        }
        std::vector<uint64_t> interval = prefTable.at(prefix);
        left = interval.at(0);
        right = interval.at(1);
        // cout << left << " " << right << endl;
    }
    uint64_t leftBound = naiveFindLeftBound(pattern, left, right);
    if (leftBound == -1) {
        result.push_back(0);
        return result;
    }
    uint64_t rightBound = naiveFindRightBound(pattern, left, right);
    result.push_back(rightBound - leftBound + 1);
    for (uint64_t i = leftBound; i <= rightBound; i++) {
        result.push_back(sa[i]);
    }
    return result;
}

uint64_t suffix_array::naiveFindLeftBound(string pattern, uint64_t left, uint64_t right) {
    cout << left << " " << right << endl;
    if (right - left == 1) {
        if (pattern.compare(text.substr(sa[left], pattern.length())) == 0) {
            return left;
        } else if (pattern.compare(text.substr(sa[right], pattern.length())) == 0) {
            return right;
        } else {
            return -1;
        }
    }
    uint64_t center = left + (right - left) / 2;
    string suffix = text.substr(sa[center], pattern.length());
    if (pattern.compare(suffix) <= 0) {
        return naiveFindLeftBound(pattern, left, center);
    } else {
        return naiveFindLeftBound(pattern, center, right);
    }
}

uint64_t suffix_array::naiveFindRightBound(string pattern, uint64_t left, uint64_t right) {
    if (right - left == 1) {
        if (pattern.compare(text.substr(sa[right], pattern.length())) == 0) {
            return right;
        } else if (pattern.compare(text.substr(sa[left], pattern.length())) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    uint64_t center = left + (right - left) / 2;
    string suffix = text.substr(sa[center], pattern.length());
    if (pattern.compare(suffix) < 0) {
        return naiveFindRightBound(pattern, left, center);
    } else {
        return naiveFindRightBound(pattern, center, right);
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
        result << "Prefix Table (k =" << k << "): " << endl;
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
