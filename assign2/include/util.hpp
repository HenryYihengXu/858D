#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <vector>

using std::string;

u_int64_t lcp(string& s1, string& s2, uint64_t s1Start, uint64_t s2Start);
std::vector<int64_t> stringWithLcpComparison(string& s1, string& s2, uint64_t s1Start, uint64_t s2Start, uint64_t s1Len, uint64_t s2Len);

#endif /* __UTIL_H__ */

    