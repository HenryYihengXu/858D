#include "../include/select_support.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;

select_support::select_support(rank_support *r) {
    this->r = r;
}

uint64_t select_support::select1(uint64_t i) {
    return 0;
}

uint64_t select_support::overhead() {
    uint64_t size = 0;
    return size;
}

void select_support::save(string& fname) {

}

void select_support::load(string& fname) {

}
