#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

#include "../include/rank_support.hpp"
#include "../include/select_support.hpp"
#include "../include/sparse_array.hpp"

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
