#include "../include/rank_support.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    compact::vector<unsigned, 1> b(3);
    rank_support r(&b);
    std::cout << "hello\n";
    std::cout << b.size() << std::endl;
    std::cout << r.rank1() << std::endl;
}