#include "../include/rank_support.hpp"

rank_support::rank_support(compact::vector<unsigned, 1> *b) 
{ 
    unsigned len = b->size();
    this->b = b;
    this->Rs = new compact::vector<unsigned>(len, len);
    this->Rb = new compact::vector<unsigned>(len, len);
    this->Rp = new compact::vector<unsigned>(len, len);
}

int rank_support::rank1() {
    std::cout << b->size() << std::endl;
    std::cout << Rs->size() << std::endl;
    std::cout << Rb->size() << std::endl;
    std::cout << Rp->size() << std::endl;

    return this->b->size();
}