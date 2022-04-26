#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>
#include <unistd.h>

#include "../include/suffix_array.hpp"
#include "../include/util.hpp"

using std::string;
using std::cout;
using std::endl;

void evaluate_buildsa(string& outputPath);
void evaluate_querysa(string& outputPath);

int main(int argc, char* argv[]) {
    string outputPath = argv[1];

    // evaluate_buildsa(outputPath);
    evaluate_querysa(outputPath); 
}

void evaluate_querysa(string& outputPath) {
    string fastas[5] = {
        "Chlamydia",
        "Coxiella",
        "Caulobacter",
        "Ecoli",
        "Pseudomonas",
    };

    uint64_t ks[5] = {
        0,
        3,
        7,
        15,
        31,
    };

    uint64_t queryLens[4] = {
        32,
        64,
        96,
        128,
    };

    string modes[2] = {
        "naive",
        "simpaccel",
    };

    std::ofstream ofile(outputPath);
    ofile << std::fixed;
    ofile << "name,k,queryLength,mode,time" << endl;

    for (string& fasta : fastas) {

        for (uint64_t k : ks) {
            string serialPath = "./data/serial/" + fasta + "." + std::to_string(k) + ".bin";
            suffix_array sa;
            sa.load(serialPath);

            for (uint64_t queryLen : queryLens) {
                string queryPath = "./data/query/" + fasta + "." + std::to_string(queryLen) + ".query";
                std::vector<string> queries = readQueries(queryPath);

                for (string& mode : modes) {
                    
                    struct timespec begin, end; 
                    clock_gettime(CLOCK_REALTIME, &begin);
                    /* time 1000 query */
                    for (uint64_t i = 0; i < queries.size(); i += 2) {
                        string query = queries.at(i + 1);
                        // cout << query << endl << endl;
                        sa.query(query, mode);
                    }
                    clock_gettime(CLOCK_REALTIME, &end);

                    long seconds = end.tv_sec - begin.tv_sec;
                    long nanoseconds = end.tv_nsec - begin.tv_nsec;
                    double elapsed = seconds + nanoseconds*1e-9;

                    ofile << fasta << "," << k << "," << queryLen << "," << mode << "," << elapsed << endl;

                }
                
            }
        }
    }

}

void evaluate_buildsa(string& outputPath) {

    string fastas[5] = {
        "Chlamydia",
        "Coxiella",
        "Caulobacter",
        "Ecoli",
        "Pseudomonas",
    };

    uint64_t ks[5] = {
        0,
        3,
        7,
        15,
        31,
    };

    // string fastas[1] = {
    //     "Chlamydia",
    // };

    // uint64_t ks[1] = {
    //     15,
    // };

    std::ofstream ofile(outputPath);
    ofile << std::fixed;
    ofile << "name,k,time" << endl;

    for (string& fasta : fastas) {
        string reference = readReference("./data/fasta/" + fasta + ".fasta");
        for (uint64_t k : ks) {
            struct timespec begin, end; 
            clock_gettime(CLOCK_REALTIME, &begin);
            /* time build sa */
            suffix_array sa(reference, k);
            clock_gettime(CLOCK_REALTIME, &end);
            // cout << sa.printPrefTable();
            // sa.query("ACTTCTCGTTTCTGGTAAACAGAGCAGTCCACA", "naive");

            long seconds = end.tv_sec - begin.tv_sec;
            long nanoseconds = end.tv_nsec - begin.tv_nsec;
            double elapsed = seconds + nanoseconds*1e-9;

            sa.save("./data/serial/" + fasta + "." + std::to_string(k) + ".bin");

            ofile << fasta << "," << k << "," << elapsed << endl;
        }
    }
}
