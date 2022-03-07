#include "../include/rank_support.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;

rank_support::rank_support(compact::vector<uint64_t, 1> *b) 
{ 
    n = b->size();
    if (n <= 1) {
        cout << "Warning: bit vector is empty or has only 1 element. Creating an empty rank_support" << endl;
        return;
    }
    RbCovers = ceil(log2(n));
    RsCovers = RbCovers * RbCovers;
    RbSize = ceil((float)n / (float)RbCovers);
    RsSize = ceil((float)n / (float)RsCovers);
    RbBits = ceil(log2(RsCovers));
    RsBits = ceil(log2(n));

    this->b = b;
    this->Rs = new compact::vector<uint64_t>(RsBits, RsSize);
    this->Rb = new compact::vector<uint64_t>(RbBits, RbSize);

    uint64_t RsCount = 0;
    uint64_t RbCount = 0;
    for (uint64_t i = 0; i < n; i++) {
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

rank_support::~rank_support() {
    if (b != NULL) {
        delete(b);
    }
    if (Rs != NULL) {
        delete(Rs);
    }
    if (Rb != NULL) {
        delete(Rb);
    }
}

uint64_t rank_support::rank1(uint64_t i) {
    if (i >= n) {
        cout << "ERROR: index out of bound!\n";
        exit(1);
    }
    uint64_t RsIdx = i / RsCovers;
    uint64_t RbIdx = i / RbCovers;
    return Rs->at(RsIdx) + Rb->at(RbIdx) + popcount(i);
}

uint64_t rank_support::overhead() {
    uint64_t size = 0;
    return size;
}

void rank_support::save(string& fname) {
    std::ofstream seqOut(fname, std::ios::binary);
    b->serialize(seqOut);
    Rs->serialize(seqOut);
    Rb->serialize(seqOut);
    seqOut.close();
}

void rank_support::load(string& fname) {
    if (b != NULL) {
        delete(b);
    }
    if (Rs != NULL) {
        free(Rs);
    }
    if (Rb != NULL) {
        free(Rb);
    }
    b = new compact::vector<uint64_t, 1>{1};
    Rs = new compact::vector<uint64_t>{1};
    Rb = new compact::vector<uint64_t>{1};

    std::ifstream seqIn("test.txt", std::ios::binary);
    b->deserialize(seqIn);
    Rs->deserialize(seqIn);
    Rb->deserialize(seqIn);
    seqIn.close();

    n = b->size();
    if (n <= 1) {
        cout << "ERROR: bit vector is empty or too short" << endl;
        exit(1);
    }
    RbCovers = ceil(log2(n));
    RsCovers = RbCovers * RbCovers;
    RbSize = ceil((float)n / (float)RbCovers);
    RsSize = ceil((float)n / (float)RsCovers);
    RbBits = ceil(log2(RsCovers));
    RsBits = ceil(log2(n));
}

uint64_t rank_support::popcount(uint64_t idx) {
    if (idx >= n) {
        cout << "ERROR: idx out of bound!\n";
        exit(1);
    }
    uint16_t *wordDataB = (uint16_t *)b->get();
    uint64_t blockStartIdx = idx / RbCovers * RbCovers;
    uint64_t wordIdx = blockStartIdx / 16;

    /* if block: the region sits in a single word */
    if (blockStartIdx % 16 + idx % RbCovers < 16) {
        uint16_t wordForBlock = wordDataB[wordIdx];
        // cout << "word for block: " << std::bitset<16>(wordForBlock) << endl;
        wordForBlock = wordForBlock >> (blockStartIdx % 16);
        wordForBlock = wordForBlock << (16 - 1 - idx % RbCovers);
        return std::popcount(wordForBlock);
    /* else block: the region sits across two words */
    } else {
        uint16_t word1ForBlock = wordDataB[wordIdx];
        uint16_t word2ForBlock = wordDataB[wordIdx + 1];
        word1ForBlock = word1ForBlock >> (blockStartIdx % 16);
        word2ForBlock = word2ForBlock << (32 - 1 - blockStartIdx % 16 - idx % RbCovers);
        return std::popcount(word1ForBlock) + std::popcount(word2ForBlock);
    }
}

/* Primarily for test purposes */
string rank_support::to_string() {
    std::stringstream result;

    result << "|";
    for (uint64_t i = 0; i < std::max(RbCovers * RbSize, RsCovers * RsSize); i++) {
        result << std::setfill(' ') << std::setw(3) << i << "|";
    }
    result << "\n";

    result << "B (bits = " << 1 << ", size = " << n << "): \n";
    result << "| ";
    for (uint64_t i = 0; i < n; i++) {
        result << b->at(i) << " | ";
    }
    result << "\n";

    result << "Rs covers " << RsCovers << " bits in B, each element of Rs contains " << RsBits << " bits , Rs contains " << RsSize << " elements\n";
    result << "Rs: \n";
    result << "|";
    for (uint64_t i = 0; i < RsSize; i++) {
        for (uint64_t j = 0; j < (RsCovers - 1) / 2; j++) {
            result << "    ";
        }
        result << " " << std::setfill(' ') << std::setw(3) << Rs->at(i);
        for (uint64_t j = 0; j < (RsCovers - 1) / 2 + ((RsCovers - 1) % 2); j++) {
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
    for (uint64_t i = 0; i < RbSize; i++) {
        for (uint64_t j = 0; j < (RbCovers - 1) / 2; j++) {
            result << "    ";
        }
        result << " " << std::setfill(' ') << std::setw(3) << Rb->at(i);
        for (uint64_t j = 0; j < (RbCovers - 1) / 2 + ((RbCovers - 1) % 2); j++) {
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

/* Only for test purposes */
uint64_t rank_support::rank1ByCount(uint64_t idx) {
    uint64_t count = 0;
    for (uint64_t i = 0; i <= idx; i++){
        count += b->at(i);
    }
    return count;
}

uint64_t rank_support::getN() {
    return n;
}

uint64_t rank_support::getRsCovers() {
    return RsCovers;
}

uint64_t rank_support::getRbCovers() {
    return RbCovers;
}

uint64_t rank_support::getRsSize() {
    return RsSize;
}

uint64_t rank_support::getRbSize() {
    return RbSize;
}

uint64_t rank_support::getRsBits() {
    return RsBits;
}

uint64_t rank_support::getRbBits() {
    return RbBits;
}

uint64_t rank_support::bAt(uint64_t i) {
    return b->at(i);
}

uint64_t rank_support::RsAt(uint64_t i) {
    return Rs->at(i);
}

uint64_t rank_support::RbAt(uint64_t i) {
    return Rb->at(i);
}

void rank_support::preExperiment() {
    b->at(0) = -1;
    Rs->at(0) = -1;
    Rs->at(1) = -1;
    Rs->at(2) = -1;
    Rb->at(0) = 11;
    cout << "size of b: " << b->size() << endl;
    cout << "size of Rs: " << Rs->size() << endl;
    cout << "size of Rb: " << Rb->size() << endl;
    cout << endl;

    cout << "bits of b: " << b->bits() << endl;
    cout << "bits of Rs: " << Rs->bits() << endl;
    cout << "bits of Rb: " << Rb->bits() << endl;
    cout << endl;

    cout << "b[0]: " << b->at(0) << endl;
    cout << "Rs[0]: " << Rs->at(0) << endl;
    cout << "Rb[0]: " << Rb->at(0) << endl;
    cout << endl;

    bool *boolDataRs = (bool *)Rs->get() + 2;
    uint16_t *wordDataRs = (uint16_t *)boolDataRs;
    uint16_t *wordDataRb = (uint16_t *)Rb->get();
    cout << "popcount of word Rs[0] " << std::bitset<16>(wordDataRs[0]) << ": " << std::popcount(wordDataRs[0]) << endl;
    cout << "popcount of word Rb[0] " << std::bitset<16>(wordDataRb[0]) << ": " << std::popcount(wordDataRb[0]) << endl;
    cout << endl;

}
