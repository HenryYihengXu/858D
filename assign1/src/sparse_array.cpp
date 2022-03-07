#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

#ifndef INCLUDE_RANK_SUPPORT
    #define INCLUDE_RANK_SUPPORT
    #include "../include/rank_support.hpp"
#endif

#ifndef INCLUDE_SELECT_SUPPORT
    #define INCLUDE_SELECT_SUPPORT
    #include "../include/select_support.hpp"
#endif

#ifndef INCLUDE_SPARSE_ARRAY
    #define INCLUDE_SPARSE_ARRAY
    #include "../include/sparse_array.hpp"
#endif

using std::string;
using std::cout;
using std::endl;

template <class T>
void sparse_array<T>::create(uint64_t size) {
    this->size = size;
    b = new compact::vector<uint64_t, 1>(size);
    r = new rank_support(b);
    cout << r->to_string();
}
