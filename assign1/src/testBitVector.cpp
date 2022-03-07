// #include <compact_vector/compact_vector.hpp>
#include "../include/compact_vector.hpp"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    unsigned bits = atoi(argv[1]);
    unsigned len = atoi(argv[2]);
    compact::vector<unsigned> ary1(bits, len);
    
    // cout << ary1.bits() << endl;
    // cout << ary1.size() << endl;
    ary1.at(0) = 3;
    // cout << ary1.at(0) << endl;
    ary1.at(1) = 4;
    // cout << ary1.at(1) << endl;
    ary1.at(2) = 5;
    // cout << ary1.at(2) << endl;
    ary1.at(3) = -1;
    // cout << ary1.at(3) << endl;

    std::ofstream seqOut("test.txt", std::ios::binary);
    ary1.serialize(seqOut);
    seqOut.close();

    compact::vector<unsigned> bitvec{1};
    std::ifstream seqIn;

    // seqIn = std::ifstream("test.txt", std::ios::binary);
    // uint64_t bits_per_element = compact::get_bits_per_element(seqIn);
    // seqIn.close();
    // bitvec.set_m_bits(bits_per_element);

    seqIn = std::ifstream("test.txt", std::ios::binary);
    bitvec.deserialize(seqIn);
    seqIn.close();

    cout << bitvec.bits() << endl;
    cout << bitvec.size() << endl;
    cout << bitvec.at(0) << endl;
    cout << bitvec.at(1) << endl;
    cout << bitvec.at(2) << endl;
    cout << bitvec.at(3) << endl;
}
