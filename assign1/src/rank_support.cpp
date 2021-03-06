#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>
#include "../include/rank_support.hpp"

using std::string;
using std::cout;
using std::endl;


rank_support::rank_support() {}

rank_support::rank_support(compact::vector<uint64_t, 1> *b) 
{ 
    n = b->size();
    if (n <= 1) {
        cout << "WARNING: bit vector is empty or has only 1 element (so logn would be 0). Creating an empty rank_support" << endl;
        return;
    }
    RbCovers = ceil(log2(n));
    RsCovers = RbCovers * RbCovers;
    RbSize = ceil((float)n / (float)RbCovers);
    RsSize = ceil((float)n / (float)RsCovers);
    RbBits = ceil(log2(RsCovers + 1));
    RsBits = ceil(log2(n + 1));
    needFreeB = false;

    this->b = b;
    this->Rs = new compact::vector<uint64_t>(RsBits, RsSize);
    this->Rb = new compact::vector<uint64_t>(RbBits, RbSize);

    this->Rs->clear_mem();
    this->Rb->clear_mem();

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
    if (b != NULL && needFreeB) {
        delete b;
    }
    if (Rs != NULL) {
        delete Rs;
    }
    if (Rb != NULL) {
        delete Rb;
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

    /*  Private simple variables: n, RbCovers, RsCovers, etc. See class def.
        Define them to avoid recomputing log, which does takes some time. 
    */
    size += 7 * 64 + 8;

    /*  Size of Rs.
        The total bits is RsSize * RsBits. However, although compact::vector stores bits, 
        it has to allocate multiples of uint64_t.
    */
    size += ceil(RsSize * RsBits / 64) * 64;

    /*  Size of Rb.
        Same argument as above.
    */
    size += RbSize * RbBits / 64 * 64;
    
    return size;
}

void rank_support::save(string& fname) {
    std::ofstream seqOut(fname, std::ios::binary);
    save(seqOut);
    seqOut.close();
}

void rank_support::save(std::ofstream& seqOut) {
    b->serialize(seqOut);
    Rs->serialize(seqOut);
    Rb->serialize(seqOut);
}

void rank_support::load(string& fname) {
    std::ifstream seqIn(fname, std::ios::binary);
    load(seqIn);
    seqIn.close();
}

void rank_support::load(std::ifstream& seqIn) {
    if (b == NULL) {
        b = new compact::vector<uint64_t, 1>(1);
        // b->clear_mem();
        needFreeB = true;
    }
    if (Rs == NULL) {
        Rs = new compact::vector<uint64_t>(1,1);
        // Rs->clear_mem();
    }
    if (Rb == NULL) {
        Rb = new compact::vector<uint64_t>(1,1);
        // Rb->clear_mem();
    }

    b->deserialize(seqIn);
    Rs->deserialize(seqIn);
    Rb->deserialize(seqIn);

    n = b->size();
    if (n <= 1) {
        cout << "WARNING: bit vector is empty or has only 1 element (so logn would be 0). Creating an empty rank_support" << endl;
        
        if (b != NULL) {
            delete b;
        }
        if (Rs != NULL) {
            delete Rs;
        }
        if (Rb != NULL) {
            delete Rb;
        }

        RbCovers = 0;
        RsCovers = 0;
        RbSize = 0;
        RsSize = 0;
        RbBits = 0;
        RsBits = 0;

        return;
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
        if (n / 16 == wordIdx) {
            wordForBlock = wordForBlock | (1UL >> (16 - n % 16));
        } 
        // cout << "word for block: " << std::bitset<16>(wordForBlock) << endl;
        wordForBlock = wordForBlock >> (blockStartIdx % 16);
        wordForBlock = wordForBlock << (16 - 1 - idx % RbCovers);
        return std::popcount(wordForBlock);
    /* else block: the region sits across two words */
    } else {
        uint16_t word1ForBlock = wordDataB[wordIdx];
        uint16_t word2ForBlock = wordDataB[wordIdx + 1];
        if (n / 16 == wordIdx + 1) {
            word2ForBlock = word2ForBlock | (1UL >> (16 - n % 16));
        } 
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

    result << "Rs: \n";
    result << "Each super-block (element of Rs) covers " << RsCovers << " bits in B, is " << RsBits << "-bit, and covers " << RbCovers << " blocks. Rs contains " << RsSize << " super-blocks.\n";
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

    result << "Rb: \n";
    result << "Each block (element of Rb) covers " << RbCovers << " bits in B and is " << RbBits << "-bit, Rb contains " << RbSize << " blocks\n";
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

uint64_t rank_support::getBAt(uint64_t i) {
    return b->at(i);
}

uint64_t rank_support::getRsAt(uint64_t i) {
    return Rs->at(i);
}

uint64_t rank_support::getRbAt(uint64_t i) {
    return Rb->at(i);
}

void rank_support::setBAt(uint64_t i, uint64_t v) {
    // b[i] = v;
    b->at(i) = v;
}

void rank_support::setRsAt(uint64_t i, uint64_t v) {
    // Rs[i] = v;
    Rs->at(i) = v;
}

void rank_support::setRbAt(uint64_t i, uint64_t v) {
    // Rb[i] = v;
    Rb->at(i) = v;
}
