#include <iostream>
#include <fstream>
#include <string>

#include "../include/suffix_array.hpp"
#include "../include/util.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char** argv) {
    string referencePath;
    string outputPath;
    uint64_t k = 0;
    if (argc == 3) {
        referencePath = argv[1];
        outputPath = argv[2];
    } else if (argc == 5) {
        k = std::stoi(argv[2]);
        referencePath = argv[3];
        outputPath = argv[4];
    } else {
        cout << "Input format doesn't match. Format: buildsa [--preftab k] reference output" << endl;
    }

    string reference = readReference(referencePath);
    suffix_array sa(reference, k);

    sa.save(outputPath);

    suffix_array saLoaded;
}
