#include <iostream>
#include <fstream>
#include <string>

#include "../include/suffix_array.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

int main(){
    const string& path = "/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/CMSC858D_S22_Project2_sample/ecoli.fa";
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string tp;
    getline(input_file, tp);
    string text = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    text = "ACTACGTACGTACG";
    text = text + "$";
    suffix_array sa(text, 3);
    cout << sa.to_string(true) << endl;
}


