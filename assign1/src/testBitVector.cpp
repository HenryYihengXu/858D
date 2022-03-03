// #include <compact_vector/compact_vector.hpp>
#include "../include/compact_vector.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "hello\n";
    unsigned bits = atoi(argv[1]);
    unsigned len = atoi(argv[2]);
    compact::vector<int> ary1(bits, len);
    
    ary1.at(0) = 3;
    std::cout << ary1.at(0) << std::endl;
    ary1.at(1) = 4;
    std::cout << ary1.at(1) << std::endl;
    ary1.at(2) = 5;
    std::cout << ary1.at(2) << std::endl;
    ary1.at(3) = -1;
    std::cout << ary1.at(3) << std::endl;
}