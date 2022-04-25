#include <sdsl/suffix_arrays.hpp>
// #include <sdsl/construct_lcp.hpp>
// #include <sdsl/construct_bwt.hpp>
// #include "gtest/gtest.h"
#include <vector>
#include <string>
// #include <map>

using namespace sdsl;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    string text = "ACTACGTACGTACG";
    text = text + "$";
    // std::basic_string<unsigned char> text = "ACTACGTACGTACG";
    int_vector<> sa(text.length(), 0, bits::hi(text.length())+1);
    algorithm::calculate_sa(reinterpret_cast<const unsigned char*>(text.c_str()), text.length(), sa);
    for (int64_t value : sa) {
        cout << value << endl;
    }
    return 0;
}
