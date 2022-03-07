#include "../include/compact_vector.hpp"
#ifndef INCLUDE_RANK_SUPPORT
    #define INCLUDE_RANK_SUPPORT
    #include "../include/rank_support.hpp"
#endif

#ifndef INCLUDE_SELECT_SUPPORT
    #define INCLUDE_SELECT_SUPPORT
    #include "../include/select_support.hpp"
#endif

#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;

template <class T>
class sparse_array {
    uint64_t size = 0;
    compact::vector<uint64_t, 1> *b = NULL;
    rank_support *r = NULL;
    std::vector<T> presentElements;

    uint64_t lastPos = 0;
    bool isPos0Avail = true;

public:
    void create(uint64_t size);
    void append(T elem, uint64_t pos);

    string to_string();
};

template <class T>
void sparse_array<T>::create(uint64_t size) {
    this->size = size;
    b = new compact::vector<uint64_t, 1>(size);
    r = new rank_support(b);
}

template <class T>
void sparse_array<T>::append(T elem, uint64_t pos) {
    if (pos >= size) {
        cout << "ERROR: Index out of bound. Stop appending.\n";
        return;
    }

    if (pos == 0 && !isPos0Avail || pos != 0 && pos <= lastPos) {
        cout << "ERROR: Insertion out of order or inserting to a position already occupied. Stop appending.\n";
        return;
    }

    isPos0Avail = false;
    lastPos = pos;

    presentElements.push_back(elem);
    b->at(pos) = 1;

    uint64_t RsCovers = r->getRsCovers();
    uint64_t RbCovers = r->getRbCovers();
    uint64_t RsSize = r->getRsSize();
    uint64_t RbSize = r->getRbSize();

    uint64_t RsIdx = pos / RsCovers;
    for (uint64_t i = RsIdx + 1; i < RsSize; i++) {
        uint64_t v = r->getRsAt(i) + 1;
        r->setRsAt(i, v);
    }

    uint64_t RbIdx = pos / RbCovers;
    // RbCovers = number of blocks in a super block, as a super block covers RbCovers^2.
    for (uint16_t i = RbIdx + 1; i < std::min(RbSize, (RsIdx + 1) * RbCovers); i++) {
        uint64_t v = r->getRbAt(i) + 1;
        r->setRbAt(i, v);
    }
}

template <class T>
string sparse_array<T>::to_string() {
    std::stringstream result;
    
    result << r->to_string() << endl;

    result << "Present elements: \n";
    result << "[";
    uint64_t presentElementsSize = presentElements.size();
    for (uint64_t i = 0; i < presentElementsSize; i++) {
        result << presentElements.at(i);
        if (i != presentElementsSize - 1) {
            result << ", ";
        }
    }
    result << "]\n\n";

    return result.str();
}
