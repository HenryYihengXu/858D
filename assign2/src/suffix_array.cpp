#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "../include/suffix_array.hpp"
#include "../include/util.hpp"

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
    
    if (k == 0) {
        return;
    }

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

std::vector<uint64_t> suffix_array::query(string pattern, string mode) {
    if (mode.compare("simpaccel") == 0) {
        return simpAccelQuery(pattern);
    } else {
        return naiveQuery(pattern);
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
    // cout << left << " " << right << endl;
    if (left == right) {
        // if (text.compare(sa[left], pattern.length(), pattern) == 0) {
        if (stringComparison(text, pattern, sa[left], 0, pattern.length(), pattern.length()) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    
    if (right - left == 1) {
        // if (text.compare(sa[left], pattern.length(), pattern) == 0) {
        if (stringComparison(text, pattern, sa[left], 0, pattern.length(), pattern.length()) == 0) {
            return left;
        // } else if (text.compare(sa[right], pattern.length(), pattern) == 0) {
        } else if (stringComparison(text, pattern, sa[right], 0, pattern.length(), pattern.length()) == 0) {
            return right;
        } else {
            return -1;
        }
    }
    
    uint64_t center = left + (right - left) / 2;

    if (text.compare(sa[center], pattern.length(), pattern) >= 0) {
        return naiveFindLeftBound(pattern, left, center);
    } else {
        return naiveFindLeftBound(pattern, center, right);
    }
}

uint64_t suffix_array::naiveFindRightBound(string pattern, uint64_t left, uint64_t right) {
    if (left == right) {
        // if (text.compare(sa[left], pattern.length(), pattern) == 0) {
        if (stringComparison(text, pattern, sa[left], 0, pattern.length(), pattern.length()) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    
    if (right - left == 1) {
        // if (text.compare(sa[right], pattern.length(), pattern) == 0) {
        if (stringComparison(text, pattern, sa[right], 0, pattern.length(), pattern.length()) == 0) {
            return right;
        // } else if (text.compare(sa[left], pattern.length(), pattern) == 0) {
        } else if (stringComparison(text, pattern, sa[left], 0, pattern.length(), pattern.length()) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    uint64_t center = left + (right - left) / 2;
    if (text.compare(sa[center], pattern.length(), pattern) > 0) {
        return naiveFindRightBound(pattern, left, center);
    } else {
        return naiveFindRightBound(pattern, center, right);
    }
}

std::vector<uint64_t> suffix_array::simpAccelQuery(string pattern) {
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

    uint64_t lcpLeft = lcp(text, pattern, sa[left], 0);
    uint64_t lcpRight = lcp(text, pattern, sa[right], 0);

    uint64_t leftBound = simpAccelFindLeftBound(pattern, left, right, lcpLeft, lcpRight);
    if (leftBound == -1) {
        result.push_back(0);
        return result;
    }
    uint64_t rightBound = simpAccelFindRightBound(pattern, left, right, lcpLeft, lcpRight);
    result.push_back(rightBound - leftBound + 1);
    for (uint64_t i = leftBound; i <= rightBound; i++) {
        result.push_back(sa[i]);
    }
    return result;
}

uint64_t suffix_array::simpAccelFindLeftBound(string pattern, uint64_t left, uint64_t right, int64_t lcpLeft, int64_t lcpRight) {
    // cout << left << " " << right << " " << lcpLeft << " " << lcpRight << endl; 
    if (left == right) {
        if (stringWithLcpComparison(text, pattern, sa[left] + lcpLeft, lcpLeft, pattern.length() - lcpLeft, pattern.length() - lcpLeft).at(0) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    if (right - left == 1) {
        if (stringWithLcpComparison(text, pattern, sa[left] + lcpLeft, lcpLeft, pattern.length() - lcpLeft, pattern.length() - lcpLeft).at(0) == 0) {
            return left;
        } else if (stringWithLcpComparison(text, pattern, sa[right] + lcpRight, lcpRight, pattern.length() - lcpRight, pattern.length() - lcpRight).at(0) == 0) {
            return right;
        } else {
            return -1;
        }
    }
    
    uint64_t center = left + (right - left) / 2;

    int64_t lcpCenter = std::min(lcpLeft, lcpRight);
    std::vector<int64_t> result = stringWithLcpComparison(text, pattern, sa[center] + lcpCenter, lcpCenter, pattern.length() - lcpCenter, pattern.length() - lcpCenter);
    // cout << "result = " << result << endl;

    if (result.at(0) == 0) {
        return simpAccelFindLeftBound(pattern, left, center, lcpLeft, lcpCenter + result.at(1));
    } else if (result.at(0) > 0) {
        return simpAccelFindLeftBound(pattern, left, center, lcpLeft, lcpCenter + result.at(1));
    } else {
        return simpAccelFindLeftBound(pattern, center, right, lcpCenter + result.at(1), lcpRight);
    }
}

uint64_t suffix_array::simpAccelFindRightBound(string pattern, uint64_t left, uint64_t right, int64_t lcpLeft, int64_t lcpRight) {
    if (left == right) {
        if (stringWithLcpComparison(text, pattern, sa[left] + lcpLeft, lcpLeft, pattern.length() - lcpLeft, pattern.length() - lcpLeft).at(0) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    
    if (right - left == 1) {
        if (stringWithLcpComparison(text, pattern, sa[right] + lcpRight, lcpRight, pattern.length() - lcpRight, pattern.length() - lcpRight).at(0) == 0) {
            return right;
        } else if (stringWithLcpComparison(text, pattern, sa[left] + lcpLeft, lcpLeft, pattern.length() - lcpLeft, pattern.length() - lcpLeft).at(0) == 0) {
            return left;
        } else {
            return -1;
        }
    }
    
    uint64_t center = left + (right - left) / 2;

    int64_t lcpCenter = std::min(lcpLeft, lcpRight);
    std::vector<int64_t> result = stringWithLcpComparison(text, pattern, sa[center] + lcpCenter, lcpCenter, pattern.length() - lcpCenter, pattern.length() - lcpCenter);

    if (result.at(0) == 0) {
        return simpAccelFindRightBound(pattern, center, right, lcpCenter + result.at(1), lcpRight);
    } else if (result.at(0) > 0) {
        return simpAccelFindRightBound(pattern, left, center, lcpLeft, lcpCenter + result.at(1));
    } else {
        return simpAccelFindRightBound(pattern, center, right, lcpCenter + result.at(1), lcpRight);
    }
}

void suffix_array::save(string path) {
    std::ofstream os(path, std::ios::binary);
    cereal::BinaryOutputArchive archive( os );

    archive( n );
    archive( k );
    archive( text );
    // archive( sa );
    sa.serialize(os);
    if (k != 0) {
        cout << endl << endl << k << endl << endl;
        archive( prefTable );
    }
}

void suffix_array::load(string path) {
    std::ifstream is(path, std::ios::binary);
    cereal::BinaryInputArchive archive( is );

    archive( n );
    archive( k );
    archive( text );
    // archive( sa );
    sa.load(is);
    if (k != 0) {
        archive( prefTable );
    }
}

string suffix_array::getText(uint64_t start, uint64_t len) {
    return text.substr(start, len);
}

string suffix_array::printPrefTable() {
    std::stringstream result;
    if (k == 0) {
        return "";
    }
    result << "Prefix Table (k = " << k << "): " << endl;
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
    return result.str();
}

string suffix_array::to_string(bool prefTable) {
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

    if (prefTable & (k != 0)) {
        result << printPrefTable();
    }

    return result.str();;
}
