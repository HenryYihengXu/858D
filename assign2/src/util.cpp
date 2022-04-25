#include <iostream>
#include <string>

#include "../include/util.hpp"

using std::string;
using std::cout;
using std::endl;

u_int64_t lcp(string& s1, string& s2, uint64_t s1Start, uint64_t s2Start) {
    uint64_t lcp = 0;
    while (s1Start < s1.length() && s2Start < s2.length()) {
        if (s1.at(s1Start) != s2.at(s2Start)) {
            break;
        }
        lcp += 1;
        s1Start += 1;
        s2Start += 1;
    }
    return lcp;
}

std::vector<int64_t> stringWithLcpComparison(string& s1, string& s2, uint64_t s1Start, uint64_t s2Start, uint64_t s1Len, uint64_t s2Len) {
    std::vector<int64_t> result;
    int64_t lcp = 0;
    while (s1Start < s1.length() && s2Start < s2.length() && lcp < s1Len && lcp < s2Len) {
        if (s1.at(s1Start) < s2.at(s2Start)) {
            result.push_back(-1);
            result.push_back(lcp);
            return result;
        } else if (s1.at(s1Start) > s2.at(s2Start)) {
            result.push_back(1);
            result.push_back(lcp);
            return result;
        } else {
            lcp += 1;
            s1Start += 1;
            s2Start += 1;
        }
    }
    if (s1Len < s2Len) {
        result.push_back(-1);
    } else if (s1Len > s2Len) {
        result.push_back(1);
    } else {
        result.push_back(0);
    }
    result.push_back(lcp);
    return result;
}
