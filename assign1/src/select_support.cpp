#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

#include "../include/rank_support.hpp"
#include "../include/select_support.hpp"

using std::string;
using std::cout;
using std::endl;


select_support::select_support(rank_support *r) {
    this->r = r;
}

select_support::~select_support() { }

uint64_t select_support::select1(uint64_t i) {
    return select1(i, 0, this->r->getN() - 1);
}

uint64_t select_support::select1(uint64_t i, uint64_t left, uint64_t right) {
    if (i == 0) {
        cout << "There is no meaning for 0th 1. Returning 0\n";
        return 0;
    }
    unsigned maxRank = r->rank1(r->getN() - 1);
    if (i > maxRank) {
        cout << "The largest rank in this bit array is " << maxRank << ", which is less than " << i << ". Returning -1\n";
        return -1;
    }

    uint64_t rank = 0;

    if (right - left == 1) {
        rank = r->rank1(left);
        if (rank == i) {
            return left;
        } else {
            return right;
        }
    }

    uint64_t mid = left + (right - left) / 2;
    rank = r->rank1(mid);
    // cout << "mid = " << mid << ", rank = " << rank << endl;
    
    if (rank == i && r->getBAt(mid) == 1) {
        return mid;
    } else if (rank < i) {
        return select1(i, mid, right);
    } else {
        return select1(i, left, mid);
    }
}

/*  Should be exactly same as rank_support, 
    as the only thing select_support wraps is a rank_support
*/
uint64_t select_support::overhead() {
    return r->overhead();
}

void select_support::save(string& fname) {
    std::ofstream seqOut(fname, std::ios::binary);
    save(seqOut);
    seqOut.close();
}

void select_support::save(std::ofstream& seqOut) {
    r->save(seqOut);
}

void select_support::load(string& fname) {
    std::ifstream seqIn(fname, std::ios::binary);
    load(seqIn);
    seqIn.close();
}

void select_support::load(std::ifstream& seqIn) {
    r->load(seqIn);
}

string select_support::to_string() {
    return r->to_string();
}

/* Only for test purposes */
uint64_t select_support::select1ByCount(uint64_t rank) {
    if (rank == 0) {
        cout << "There is no meaning for 0th 1. Returning 0\n";
        return 0;
    }
    uint64_t count = 0;
    for (unsigned i = 0; i < r->getN(); i++) {
        if (r->getBAt(i) == 1) {
            count++;
        }
        if (count == rank) {
            return i;
        }
    }
    cout << "The largest rank in this bit array is " << count << ", which is less than " << rank << ". Returning -1\n";
    return -1;
}
