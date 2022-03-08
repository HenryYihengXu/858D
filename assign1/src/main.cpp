#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>

#ifndef INCLUDE_RANK_SUPPORT
    #define INCLUDE_RANK_SUPPORT
    #include "../include/rank_support.hpp"
#endif

#ifndef INCLUDE_SELECT_SUPPORT
    #define INCLUDE_SELECT_SUPPORT
    #include "../include/select_support.hpp"
#endif

#ifndef INCLUDE_SPARSE_ARRAY
    #define INCLUDE_SPARSE_ARRAY
    #include "../include/sparse_array.hpp"
#endif

using std::string;
using std::cout;
using std::endl;

void test_rank1(uint64_t num_test=10);
void test_select1(uint64_t num_test=10);
void test_save_load_r();
void test_save_load_s();
void test_create_append();
void test_sparse_array();
void test_save_load_sparse_array();
int generate_random_01(float oneFreq=0.5);
compact::vector<uint64_t, 1> generate_random_bit_vector(uint64_t size, float oneFreq=0.5);
sparse_array<string> generate_random_sparse_array(uint64_t size, float sparsity);

int main(int argc, char* argv[]) {
    // uint64_t n = atoi(argv[1]);
    // float oneFreq = atof(argv[2]);

    // string a = "sdfa\n";
    // cout << decltype(a) << endl;

    srand(time(NULL));
    // test_rank1();
    test_select1();
    // test_save_load_r();
    // test_save_load_s();
    // test_create_append();
    // test_sparse_array();
    // test_save_load_sparse_array();
}

void test_rank1(uint64_t num_test) {
    uint64_t passed = 0;
    for (uint64_t i = 0; i < num_test; i++) {
        uint64_t n = 16 + rand() % 64;
        float oneFreq = (float)(rand()) / (float)RAND_MAX;
        compact::vector<uint64_t, 1> b = generate_random_bit_vector(n, oneFreq);
        rank_support r(&b);

        uint64_t idx = rand() % n;
        uint64_t rank1 = r.rank1(idx);
        uint64_t rank1ByCount = r.rank1ByCount(idx);
        cout << "Test " << i << ": size = " << n << ", one frequency = " << oneFreq << 
            ", index = " << idx << ", rank 1 = " << rank1 << ", rank 1 by count = " << rank1ByCount << endl;
        cout << r.to_string();
        
        if (rank1 == rank1ByCount) {
            cout << "passed\n";
            passed++;
        } else {
            cout << "failed\n";
        }
        cout << "\n";
    }

    if (passed == num_test) {
        cout << "ALL TESTS PASSED\n";
    } else {
        cout << "SOME TESTS FAILED\n";
    }
    cout << "\n";
}

void test_select1(uint64_t num_test) {
    uint64_t passed = 0;
    for (uint64_t i = 0; i < num_test; i++) {
        uint64_t n = 16 + rand() % 64;
        float oneFreq = (float)(rand()) / (float)RAND_MAX;
        compact::vector<uint64_t, 1> b = generate_random_bit_vector(n, oneFreq);
        rank_support r(&b);
        select_support s(&r);

        unsigned maxRank = r.rank1(n - 1);
        if (maxRank == 0) {
            i--;
            continue;
        }
        uint64_t rank = rand() % maxRank;
        unsigned select1 = s.select1(rank);
        unsigned select1ByCount = s.select1ByCount(rank);
        uint64_t idx = rand() % n;
        cout << "Test " << i << ": r size = " << n << ", one frequency = " << oneFreq << 
            ", rank to select = " << rank << ", select 1 = " << select1 << ", select 1 by count = " << select1ByCount << endl;
        cout << r.to_string();

        if (select1 == select1ByCount) {
            cout << "passed\n";
            passed++;
        } else {
            cout << "failed\n";
        }
        cout << "\n";
    }

    if (passed == num_test) {
        cout << "ALL TESTS PASSED\n";
    } else {
        cout << "SOME TESTS FAILED\n";
    }
    cout << "\n";
}

void test_save_load_r() {
    uint64_t n = 16 + rand() % 64;
    float oneFreq = (float)(rand()) / (float)RAND_MAX;

    compact::vector<uint64_t, 1> b = generate_random_bit_vector(n, oneFreq);
    rank_support r(&b);
    cout << r.to_string() << endl;
    string fname = "test.txt";
    r.save(fname);

    r.load(fname);
    cout << r.to_string() << endl;

    n = 16 + rand() % 64;
    oneFreq = (float)(rand()) / (float)RAND_MAX;
    compact::vector<uint64_t, 1> b2 = generate_random_bit_vector(n, oneFreq);
    rank_support r2 = rank_support(&b2);
    cout << r2.to_string() << endl;
    r2.load(fname);
    cout << r2.to_string() << endl;
}

void test_save_load_s() {
    uint64_t n = 16 + rand() % 64;
    float oneFreq = (float)(rand()) / (float)RAND_MAX;
    compact::vector<uint64_t, 1> b = generate_random_bit_vector(n, oneFreq);
    rank_support r(&b);
    select_support s(&r);
    cout << s.to_string() << endl;
    string fname = "test.txt";
    s.save(fname);

    s.load(fname);
    cout << s.to_string() << endl;

    n = 16 + rand() % 64;
    oneFreq = (float)(rand()) / (float)RAND_MAX;
    compact::vector<uint64_t, 1> b2 = generate_random_bit_vector(n, oneFreq);
    rank_support r2(&b2);
    select_support s2(&r2);
    cout << s2.to_string() << endl;
    s2.load(fname);
    cout << s2.to_string() << endl;
}

void test_create_append() {
    sparse_array<string> sa{};
    sa.create(60);
    cout << sa.to_string();
    sa.append("a", 0);
    cout << sa.to_string();
    sa.append("x", 0);
    cout << sa.to_string();
    sa.append("b", 8);
    cout << sa.to_string();
    sa.append("c", 21);
    cout << sa.to_string();
    sa.append("x", 18);
    cout << sa.to_string();
    sa.append("x", 21);
    cout << sa.to_string();
    sa.append("d", 29);
    cout << sa.to_string();
    sa.append("e", 38);
    cout << sa.to_string();
    sa.append("x", 60);
    cout << sa.to_string();
    sa.append("f", 45);
    cout << sa.to_string();
    sa.append("g", 57);
    cout << sa.to_string();
    sa.append("x", 60);
    cout << sa.to_string();
    sa.append("x", 61);
    cout << sa.to_string();
}

void test_sparse_array() {
    uint64_t n = 16 + rand() % 64;
    float sparsity = (float)(rand()) / (float)RAND_MAX;
    sparse_array<string> sa = generate_random_sparse_array(n, sparsity);

    cout << sa.to_string() << endl << endl;
    uint64_t saSize = sa.size();
    uint64_t elemSize = sa.num_elem();
    cout << "sparse array size: " << saSize << endl;
    cout << "present elements size: " << elemSize << endl;

    string ss = "";
    string &s = ss;

    for (uint64_t i = 0; i <= elemSize; i++) {
        if (sa.get_at_rank(i, s)) {
            cout << "element " << i << ": " << s << endl;
        } else {
            cout << "element " << i << ": " << "index out of bound" << endl;
        }
    }

    cout << endl << endl;

    for (uint64_t i = 0; i <= saSize; i++) {
        uint64_t num_elem = sa.num_elem_at(i);
        if (sa.get_at_index(i, s)) {
            cout << "element at index " << i << ": " << s << ".           num elements up to here: " << num_elem << endl;
        } else {
            cout << "no element at index " << i << ".           num elements up to here: " << num_elem << endl;
        }
    }

    cout << endl << endl;
}

void test_save_load_sparse_array() {
    uint64_t n = 16 + rand() % 64;
    float sparsity = (float)(rand()) / (float)RAND_MAX;
    sparse_array<string> sa = generate_random_sparse_array(n, sparsity);
    cout << sa.to_string() << endl;
    string fname = "test.txt";
    sa.save(fname);

    sa.load(fname);
    cout << sa.to_string() << endl;
    
    n = 16 + rand() % 64;
    sparsity = (float)(rand()) / (float)RAND_MAX;
    sparse_array<string> sa2 = generate_random_sparse_array(n, sparsity);
    cout << sa2.to_string() << endl;
    sa2.load(fname);
    cout << sa2.to_string() << endl;
}

int generate_random_01(float oneFreq) {
    float r = (float)(rand()) / (float)RAND_MAX;
    if (r > oneFreq) {
        return 0;
    } else {
        return 1;
    }
}

compact::vector<uint64_t, 1> generate_random_bit_vector(uint64_t size, float oneFreq) {
    compact::vector<uint64_t, 1> b(size);
    for (uint64_t i = 0; i < b.size(); i++) {
        b.at(i) = generate_random_01(oneFreq);
    }
    return b;
}

sparse_array<string> generate_random_sparse_array(uint64_t size, float sparsity) {
    compact::vector<uint64_t, 1> b = generate_random_bit_vector(size, 1 - sparsity);

    sparse_array<string> sa{};
    sa.create(size);

    uint64_t count = 0;
    for (uint64_t i = 0; i < b.size(); i++) {
        if (b.at(i) == 1) {
            count++;
            sa.append(std::to_string(count), i);
        }
    }

    return sa;
}
