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
    rank_support *r = NULL;
    std::vector<T> *presentElements = NULL;

    uint64_t lastPos = 0;

public:
    ~sparse_array();
    void create(uint64_t size);
    void append(T elem, uint64_t pos);
    bool get_at_rank(uint64_t r, T& elem);
    bool get_at_index(uint64_t r, T& elem);
    uint64_t num_elem_at(uint64_t r);
    uint64_t size();
    uint64_t num_elem();
    void save(string& fname);
    void load(string& fname);

    void save(std::ofstream& seqOut);
    void load(std::ifstream& seqIn);
    string to_string();
};

template <class T>
sparse_array<T>::~sparse_array() {
    if (r != NULL) {
        delete(r);
    }
}

template <class T>
void sparse_array<T>::create(uint64_t size) {
    compact::vector<uint64_t, 1> *b = new compact::vector<uint64_t, 1>(size);
    r = new rank_support(b);
    presentElements = new std::vector<T>{};
}

template <class T>
void sparse_array<T>::append(T elem, uint64_t pos) {
    if (r == NULL) {
        cout << "ERROR: Array is not created. Stop appending.\n";
        return;
    }

    if (pos >= r->getN()) {
        cout << "ERROR: Index out of bound. Stop appending.\n";
        return;
    }

    if (pos == 0 && presentElements->size() != 0 || pos != 0 && pos <= lastPos) {
        cout << "ERROR: Insertion out of order or inserting to a position already occupied. Stop appending.\n";
        return;
    }

    lastPos = pos;

    presentElements->push_back(elem);
    r->setBAt(pos, 1);

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
bool sparse_array<T>::get_at_rank(uint64_t r, T& elem) {
    if (this->r == NULL) {
        cout << "ERROR: Array is not created. Returning false.\n";
        return false;
    }

    if (r >= presentElements->size()) {
        return false;
    }

    elem = presentElements->at(r);
    return true;
}

template <class T>
bool sparse_array<T>::get_at_index(uint64_t r, T& elem) {
    if (this->r == NULL) {
        cout << "ERROR: Array is not created. Returning false.\n";
        return false;
    }

    if (r >= this->r->getN()) {
        cout << "ERROR: Index out of bound. Returning false.\n";
        return false;
    }

    if (this->r->getBAt(r) == 0) {
        return false;
    }

    uint64_t elemIdx = this->r->rank1(r) - 1;
    elem = presentElements->at(elemIdx);
    return true;
}

template <class T>
uint64_t sparse_array<T>::num_elem_at(uint64_t r) {
    if (this->r == NULL) {
        cout << "ERROR: Array is not created. Returning 0.\n";
        return 0;
    }

    if (r >= this->r->getN()) {
        cout << "ERROR: Index out of bound. Returning total number of present elements.\n";
        return presentElements->size();
    }

    return this->r->rank1(r);
}

template <class T>
uint64_t sparse_array<T>::size() {
    if (r == NULL) {
        cout << "ERROR: Array is not created. Returning 0.\n";
        return 0;
    }
    return r->getN();
}

template <class T>
uint64_t sparse_array<T>::num_elem() {
    if (r == NULL) {
        cout << "ERROR: Array is not created. Returning 0.\n";
        return 0;
    }
    return presentElements->size();
}

template <class T>
void sparse_array<T>::save(string& fname) {
    std::ofstream seqOut(fname, std::ios::binary);
    save(seqOut);
    seqOut.close();
}

template <class T>
void sparse_array<T>::save(std::ofstream& seqOut) {
    r->save(seqOut);

    uint64_t num_elem = presentElements->size();
    seqOut.write(reinterpret_cast<char *>(&num_elem), sizeof(num_elem));

    seqOut.write(reinterpret_cast<char *>(presentElements), sizeof(T) * num_elem);
    // for (uint64_t i = 0; i < num_elem; i++) {
    //     seqOut.write(reinterpret_cast<char *>(&presentElements[i]), sizeof(T));
    // }
}

template <class T>
void sparse_array<T>::load(string& fname) {
    std::ifstream seqIn(fname, std::ios::binary);
    load(seqIn);
    seqIn.close();
}

template <class T>
void sparse_array<T>::load(std::ifstream& seqIn) {
    if (presentElements != NULL) {
        free(presentElements);
    }
    if (r == NULL) {
        r = new rank_support();
    }

    r->load(seqIn);

    uint64_t num_elem = 0;
    seqIn.read(reinterpret_cast<char *>(&num_elem), sizeof(num_elem));
    presentElements = new std::vector<T>(num_elem);
    seqIn.read(reinterpret_cast<char *>(presentElements), sizeof(T) * num_elem);
}

template <class T>
string sparse_array<T>::to_string() {
    std::stringstream result;
    
    result << r->to_string();

    result << "Present elements: \n";
    result << "[";
    uint64_t presentElementsSize = presentElements->size();
    for (uint64_t i = 0; i < presentElementsSize; i++) {
        result << presentElements->at(i);
        if (i != presentElementsSize - 1) {
            result << ", ";
        }
    }
    result << "]\n\n";

    return result.str();
}
