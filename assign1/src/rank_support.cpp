#include "../include/rank_support.hpp"
#include <iostream>
#include <math.h>

rank_support::rank_support(compact::vector<unsigned, 1> *b) 
{ 
    unsigned n = b->size();
    unsigned bCovers = n;
    unsigned RbCovers = ceil(log2(bCovers));
    unsigned RsCovers = RbCovers * RbCovers;
    unsigned RbSize = ceil((float)n / (float)RbCovers);
    unsigned RsSize = ceil((float)n / (float)RsCovers);
    unsigned RbBits = ceil(log2(RsCovers));
    unsigned RsBits = ceil(log2(bCovers));

    this->b = b;
    this->Rs = new compact::vector<unsigned>(RsBits, RsSize);
    this->Rb = new compact::vector<unsigned>(RbBits, RbSize);
}

int rank_support::rank1(unsigned idx) {
    return idx;
}

void rank_support::preExperiment() {
    b->at(0) = -1;
    Rs->at(0) = -1;
    Rs->at(1) = 1;
    Rb->at(0) = 11;
    std::cout << "size of b: " << b->size() << std::endl;
    std::cout << "size of Rs: " << Rs->size() << std::endl;
    std::cout << "size of Rb: " << Rb->size() << std::endl;
    std::cout << std::endl;

    std::cout << "bits of b: " << b->bits() << std::endl;
    std::cout << "bits of Rs: " << Rs->bits() << std::endl;
    std::cout << "bits of Rb: " << Rb->bits() << std::endl;
    std::cout << std::endl;

    std::cout << "b[0]: " << b->at(0) << std::endl;
    std::cout << "Rs[0]: " << Rs->at(0) << std::endl;
    std::cout << "Rb[0]: " << Rb->at(0) << std::endl;
    std::cout << std::endl;

    uint8_t *wordDataRs = (uint8_t *)Rs->get() + 1;
    uint8_t *wordDataRb = (uint8_t *)Rb->get();
    std::cout << "popcount of word Rs[0]: " << std::popcount(wordDataRs[0]) << std::endl;
    std::cout << "popcount of word Rb[0]: " << std::popcount(wordDataRb[0]) << std::endl;
    std::cout << std::endl;

}
