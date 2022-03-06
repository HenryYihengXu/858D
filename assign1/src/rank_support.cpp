#include "../include/rank_support.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip> 

rank_support::rank_support(compact::vector<unsigned, 1> *b) 
{ 
    n = b->size();
    RbCovers = ceil(log2(n));
    RsCovers = RbCovers * RbCovers;
    RbSize = ceil((float)n / (float)RbCovers);
    RsSize = ceil((float)n / (float)RsCovers);
    RbBits = ceil(log2(RsCovers));
    RsBits = ceil(log2(n));

    this->b = b;
    this->Rs = new compact::vector<unsigned>(RsBits, RsSize);
    this->Rb = new compact::vector<unsigned>(RbBits, RbSize);

    unsigned RsCount = 0;
    unsigned RbCount = 0;
    for (unsigned i = 0; i < n; i++) {
        if (i % RsCovers == 0) {
            Rs->at(i / RsCovers) = RsCount;
            RbCount = 0;
        }
        if (i % RbCovers == 0) {
            Rb->at(i / RbCovers) = RbCount;
        }
        if (b->at(i) == 1) {
            RsCount++;
            RbCount++;
        }
    }
}

unsigned rank_support::rank1(unsigned idx) {
    unsigned RsIdx = idx / RsCovers;
    unsigned RbIdx = idx / RbCovers;
    return Rs->at(RsIdx) + Rb->at(RbIdx) + popcount(idx);
}

unsigned rank_support::popcount(unsigned idx) {
    uint16_t *wordDataB = (uint16_t *)b->get();
    unsigned blockStartIdx = idx / RbCovers * RbCovers;
    unsigned wordIdx = blockStartIdx / 16;

    if (blockStartIdx % 16 + RbCovers <= 16) {
        uint16_t wordForBlock = wordDataB[wordIdx];
        std::cout << "word for block: " << std::bitset<16>(wordForBlock) << std::endl;
        wordForBlock = wordForBlock >> (blockStartIdx % 16);
        wordForBlock = wordForBlock << (16 - RbCovers);
        std::cout << "word for block: " << std::bitset<16>(wordForBlock) << std::endl;
        return std::popcount(wordForBlock);
    } else {
        uint16_t word1ForBlock = wordDataB[wordIdx];
        uint16_t word2ForBlock = wordDataB[wordIdx + 1];
        std::cout << "word 1 for block: " << std::bitset<16>(word1ForBlock) << std::endl;
        std::cout << "word 2 for block: " << std::bitset<16>(word2ForBlock) << std::endl;
        word1ForBlock = word1ForBlock >> (blockStartIdx % 16);
        word2ForBlock = word2ForBlock << (32 - blockStartIdx % 16 - RbCovers);
        std::cout << "word 1 for block: " << std::bitset<16>(word1ForBlock) << std::endl;
        std::cout << "word 2 for block: " << std::bitset<16>(word2ForBlock) << std::endl;
        return std::popcount(word1ForBlock) + std::popcount(word2ForBlock);
    }
}

std::string rank_support::to_string() {
    std::stringstream result;

    result << "|";
    for (unsigned i = 0; i < std::max(RbCovers * RbSize, RsCovers * RsSize); i++) {
        result << std::setfill(' ') << std::setw(3) << i << "|";
    }
    result << "\n";

    result << "B (bits = " << 1 << ", size = " << n << "): \n";
    result << "| ";
    for (unsigned i = 0; i < n; i++) {
        result << b->at(i) << " | ";
    }
    result << "\n";

    result << "Rs covers " << RsCovers << " bits in B, each element of Rs contains " << RsBits << " bits , Rs contains " << RsSize << " elements\n";
    result << "Rs: \n";
    result << "|";
    for (unsigned i = 0; i < RsSize; i++) {
        for (unsigned j = 0; j < (RsCovers - 1) / 2; j++) {
            result << "    ";
        }
        result << " " << std::setfill(' ') << std::setw(3) << Rs->at(i);
        for (unsigned j = 0; j < (RsCovers - 1) / 2 + ((RsCovers - 1) % 2); j++) {
            if (j == (RsCovers - 1) / 2 + ((RsCovers - 1) % 2) - 1) {
                result << "   ";
            } else {
                result << "    ";
            }
        }
        result << "|";
    }
    result << "\n";

    result << "Rb covers " << RbCovers << " bits in B, each element of Rb contains " << RbBits << " bits , Rb contains " << RbSize << " elements\n";
    result << "Rb: \n";
    result << "|";
    for (unsigned i = 0; i < RbSize; i++) {
        for (unsigned j = 0; j < (RbCovers - 1) / 2; j++) {
            result << "    ";
        }
        result << " " << std::setfill(' ') << std::setw(3) << Rb->at(i);
        for (unsigned j = 0; j < (RbCovers - 1) / 2 + ((RbCovers - 1) % 2); j++) {
            if (j == (RbCovers - 1) / 2 + ((RbCovers - 1) % 2) - 1) {
                result << "   ";
            } else {
                result << "    ";
            }
        }
        result << "|";
    }
    
    result << "\n";
    result << "\n";
    
    return result.str();
}

unsigned rank_support::countRank1(unsigned idx) {
    unsigned count = 0;
    for (unsigned i = 0; i < idx; i++){
        count += b->at(i);
    }
    return count;
}

void rank_support::preExperiment() {
    b->at(0) = -1;
    Rs->at(0) = -1;
    Rs->at(1) = -1;
    Rs->at(2) = -1;
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

    bool *boolDataRs = (bool *)Rs->get() + 2;
    uint16_t *wordDataRs = (uint16_t *)boolDataRs;
    uint16_t *wordDataRb = (uint16_t *)Rb->get();
    std::cout << "popcount of word Rs[0] " << std::bitset<16>(wordDataRs[0]) << ": " << std::popcount(wordDataRs[0]) << std::endl;
    std::cout << "popcount of word Rb[0] " << std::bitset<16>(wordDataRb[0]) << ": " << std::popcount(wordDataRb[0]) << std::endl;
    std::cout << std::endl;

}
