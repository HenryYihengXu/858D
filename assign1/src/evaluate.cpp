#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>
#include <unistd.h>

#include "../include/rank_support.hpp"
#include "../include/select_support.hpp"
#include "../include/sparse_array.hpp"
#include "../include/util.hpp"

using std::string;
using std::cout;
using std::endl;

void evaluate_rank_support(string& fname);
void evaluate_select_support(string& fname);
void evaluate_sparse_array(string& fname);

int main(int argc, char* argv[]) {
    string fname = argv[1];

    // evaluate_rank_support(fname);
    // evaluate_select_support(fname);
    evaluate_sparse_array(fname);
}

void evaluate_rank_support(string& fname) {
    srand(time(NULL));

    std::ofstream ofile(fname);
    ofile << std::fixed;
    ofile << "bit-vector size,time,space overhead,n" << endl;

    for (uint64_t n = 1000; n <= 1000000; n += 1000) {
        compact::vector<uint64_t, 1> b = generate_random_bit_vector(n, 0.5);
        rank_support r(&b);
        uint64_t overhead = r.overhead();

        struct timespec begin, end; 
        clock_gettime(CLOCK_REALTIME, &begin);
        /* do 1000 rank operations and time it */
        for (uint64_t i = 0; i < 1000; i++) {
            uint64_t idx = rand() % n;
            uint64_t rank = r.rank1(idx);
        }
        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        ofile << n << "," << elapsed << "," << overhead << "," << n << endl;
    }
}

void evaluate_select_support(string& fname) {
    srand(time(NULL));

    std::ofstream ofile(fname);
    ofile << std::fixed;
    ofile << "bit-vector size,time,space overhead,n" << endl;

    for (uint64_t n = 1000; n <= 1000000; n += 1000) {
        compact::vector<uint64_t, 1> b = generate_random_bit_vector(n, 0.5);
        rank_support r(&b);
        select_support s(&r);
        uint64_t overhead = s.overhead();

        unsigned maxRank = r.rank1(n - 1);
        if (maxRank == 0) {
            maxRank = 1; // This select will be out of bound. But it's okay. It's handled and we just want to get time.
        }

        struct timespec begin, end; 
        clock_gettime(CLOCK_REALTIME, &begin);
        /* do 1000 select operations and time it */
        for (uint64_t i = 0; i < 1000; i++) {
            uint64_t rank = 1 + rand() % maxRank;
            unsigned select1 = s.select1(rank);
        }
        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        ofile << n << "," << elapsed << "," << overhead << "," << n << endl;
    }
}

void evaluate_sparse_array(string& fname) {
    srand(time(NULL));

    std::ofstream ofile(fname);
    ofile << std::fixed;
    ofile << "sparsity,length,time_create_append,time_get_at_rank,time_get_at_index,time_num_elem_at,space,saving" << endl;
    
    float sparsities[4] = {0.01, 0.05, 0.1, 0.2};
    // float sparsities[1] = {0.01};

    for (float sparsity : sparsities) {
        for (uint64_t n = 5000; n <= 1000000; n += 5000) {
            struct timespec begin, end;
            long seconds, nanoseconds;
            double elapsed;

            ofile << sparsity << "," << n << ",";

            clock_gettime(CLOCK_REALTIME, &begin);
            sparse_array<string> sa = generate_random_sparse_array(n, sparsity);
            clock_gettime(CLOCK_REALTIME, &end);
            seconds = end.tv_sec - begin.tv_sec;
            nanoseconds = end.tv_nsec - begin.tv_nsec;
            elapsed = seconds + nanoseconds*1e-9;
            ofile << elapsed << ",";

            string ss = "";
            string &s = ss;
            
            uint64_t num_elem = sa.num_elem();
            if (num_elem == 0) {
                num_elem = 1; // The get_at_rank will be out of bound. But it's okay. It's handled and we just want to get time.
            }
            clock_gettime(CLOCK_REALTIME, &begin);
            for (uint64_t i = 0; i < 1000; i++) {
                uint64_t rank = rand() % num_elem;
                sa.get_at_rank(rank, s);
            }
            clock_gettime(CLOCK_REALTIME, &end);
            seconds = end.tv_sec - begin.tv_sec;
            nanoseconds = end.tv_nsec - begin.tv_nsec;
            elapsed = seconds + nanoseconds*1e-9;
            ofile << elapsed << ",";            

            uint64_t size = sa.size();
            clock_gettime(CLOCK_REALTIME, &begin);
            for (uint64_t i = 0; i < 1000; i++) {
                uint64_t idx = rand() % size;
                // try {
                //     sa.get_at_index(idx, s);
                // } catch (...) {
                //     cout << "n = " << n << ", idx = " << idx << '\n';
                // }
                sa.get_at_index(idx, s);
            }
            clock_gettime(CLOCK_REALTIME, &end);
            seconds = end.tv_sec - begin.tv_sec;
            nanoseconds = end.tv_nsec - begin.tv_nsec;
            elapsed = seconds + nanoseconds*1e-9;
            ofile << elapsed << ",";      

            clock_gettime(CLOCK_REALTIME, &begin);
            for (uint64_t i = 0; i < 1000; i++) {
                uint64_t idx = rand() % size;
                uint64_t num = sa.num_elem_at(idx);
            }
            clock_gettime(CLOCK_REALTIME, &end);
            seconds = end.tv_sec - begin.tv_sec;
            nanoseconds = end.tv_nsec - begin.tv_nsec;
            elapsed = seconds + nanoseconds*1e-9;
            ofile << elapsed << ",";  
            
            uint64_t space = sa.space();
            ofile << space << ",";  

            /* each empty string takes 4 bytes to store the pointer */
            uint64_t saving = (size - num_elem) * 4 * 8;
            ofile << saving << endl;  
        }
    }
}
