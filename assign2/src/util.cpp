#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include <time.h>

#include "../include/util.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

string readReference(string path) {
    std::ifstream referenceFile(path);
    if (!referenceFile.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string reference = "";
    // string reference = string((std::istreambuf_iterator<char>(referenceFile)), std::istreambuf_iterator<char>());
    string line;
    srand(time(NULL));
    while(getline(referenceFile, line)) {
        float r = (float)(rand()) / (float)RAND_MAX;
        if (line.empty()) {
            continue;
        }
        if (line.at(0) == '>') {
            continue;
        }
        for (uint64_t i = 0; i < line.length(); i++) {
            char c = line.at(i);
            switch (c)
            {
            case 'a':
                line.at(i) = 'A';
                break;
            case 'c':
                line.at(i) = 'C';
                break;
            case 'g':
                line.at(i) = 'G';
                break;
            case 't':
                line.at(i) = 'T';
                break;
            case 'n':
                if (r <= 0.25) {
                    line.at(i) = 'A';
                } else if (r <= 0.5) {
                    line.at(i) = 'C';
                } else if (r <= 0.75) {
                    line.at(i) = 'G';
                } else {
                    line.at(i) = 'T';
                }
                break;
            case 'N':
                if (r <= 0.25) {
                    line.at(i) = 'A';
                } else if (r <= 0.5) {
                    line.at(i) = 'C';
                } else if (r <= 0.75) {
                    line.at(i) = 'G';
                } else {
                    line.at(i) = 'T';
                }
                break;
            default:
                break;
            }
        }
        reference.append(line);
    }
    reference.push_back('$');
    referenceFile.close();
    return reference;
}

std::vector<string> readQueries(string path) {
    std::vector<string> queries;
    std::ifstream queryFile(path);
    if (!queryFile.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while(getline(queryFile, line)){ 
        if (line.empty()) {
            continue;
        }
        string name = line.substr(1);
        queries.push_back(name);
        getline(queryFile, line);
        if (line.empty()) {
            continue;
        }
        queries.push_back(line);
    }
    queryFile.close();
    return queries;
}

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

int stringComparison(string& s1, string& s2, uint64_t s1Start, uint64_t s2Start, uint64_t s1Len, uint64_t s2Len) {
    int64_t lcp = 0;
    while (s1Start < s1.length() && s2Start < s2.length() && lcp < s1Len && lcp < s2Len) {
        if (s1.at(s1Start) < s2.at(s2Start)) {
            return -1;
        } else if (s1.at(s1Start) > s2.at(s2Start)) {
            return 1;
        } else {
            lcp += 1;
            s1Start += 1;
            s2Start += 1;
        }
    }
    if (s1Len < s2Len) {
        return -1;
    } else if (s1Len > s2Len) {
        return 1;
    } else {
        return 0;
    }
}

