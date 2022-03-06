// #include <compact_vector/compact_vector.hpp>
#include "../include/compact_vector.hpp"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    cout << "hello\n";
    unsigned bits = atoi(argv[1]);
    unsigned len = atoi(argv[2]);
    compact::vector<unsigned> ary1(bits, len);
    
    cout << ary1.size() << endl;
    ary1.at(0) = 3;
    cout << ary1.at(0) << endl;
    ary1.at(1) = 4;
    cout << ary1.at(1) << endl;
    ary1.at(2) = 5;
    cout << ary1.at(2) << endl;
    ary1.at(3) = -1;
    cout << ary1.at(3) << endl;
}