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
    return select1(i, 0, this->r->getN() - 1);
}

uint64_t select_support::select1(uint64_t i, uint64_t left, uint64_t right) {
    if (i == 0) {
        cout << "There is no meaning for 0th 1. Returning -1\n";
        return -1;
    }

    uint64_t rank = 0;

    if (right - left == 1) {
        rank = r->rank1(left);
        if (rank == i) {
            return left;
        } else {
            rank = r->rank1(right);
            if (rank < i) {
                cout << "The largest rank in this bit array is " << rank << ", which is less than " << i << ". Returning -1\n";
                return -1;
            } else {
                return right;
            }
        }
    }

    uint64_t mid = left + (right - left) / 2;
    rank = r->rank1(mid);
    cout << "mid = " << mid << ", rank = " << rank << endl;
    
    if (rank == i && r->bAt(mid) == 1) {
        return mid;
    } else if (rank < i) {
        return select1(i, mid, right);
    } else {
        return select1(i, left, mid);
    }
}

uint64_t select_support::overhead() {
    uint64_t size = 0;
    return size;
}

void select_support::save(string& fname) {

}

void select_support::load(string& fname) {

}

/* Only for test purposes */
uint64_t select_support::select1ByCount(uint64_t rank) {
    if (rank == 0) {
        cout << "There is no meaning for 0th 1. Returning -1\n";
        return -1;
    }
    uint64_t count = 0;
    for (unsigned i = 0; i < r->getN(); i++) {
        if (r->bAt(i) == 1) {
            count++;
        }
        if (count == rank) {
            return i;
        }
    }
    cout << "The largest rank in this bit array is " << count << ", which is less than " << rank << ". Returning -1\n";
    return -1;
}
