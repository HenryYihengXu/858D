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
    if (argc != 5) {
        cout << "Input format doesn't match. Format: querysa index queries query_mode output" << endl;
    }

    string binaryPath = argv[1];
    suffix_array sa;
    sa.load(binaryPath);

    string queryFilePath = argv[2];
    string queryMode = argv[3];
    std::vector<string> queries = readQueries(queryFilePath);

    std::unordered_map<string, std::vector<uint64_t>> results;
    for (uint64_t i = 0; i < queries.size(); i += 2) {
        string name = queries.at(i);
        string query = queries.at(i + 1);
        std::vector<uint64_t> result = sa.query(query, queryMode);
        results.insert({name, result});
    }

    string outputFilePath = argv[4];
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        cerr << "Could not open the file - '"
             << outputFilePath << "'" << endl;
        exit(EXIT_FAILURE);
    }

    // // Just to compare with query_res.txt, which is sorted by name string
    // std::vector<string> keys;
    // keys.reserve(results.size());
    // for (auto& it : results) {
    //     keys.push_back(it.first);
    // }
    // std::sort (keys.begin(), keys.end());
    // for(string key : keys) {
    //     std::vector<uint64_t> result = results[key];
    //     outputFile << key << "\t";
    //     for (uint64_t i : result) {
    //         outputFile << i << "\t"; 
    //     }
    //     outputFile << endl;
    // }

    for (uint64_t i = 0; i < queries.size(); i += 2) {
        string name = queries.at(i);
        std::vector<uint64_t> result = results[name];
        outputFile << name << "\t";
        for (uint64_t i : result) {
            outputFile << i << "\t"; 
        }
        outputFile << endl;
    }

    outputFile.close(); 
}
