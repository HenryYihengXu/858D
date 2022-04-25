#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

int main(){
    // fstream newfile;
    // newfile.open("/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/CMSC858D_S22_Project2_sample/ecoli.fa",ios::in);  // open a file to perform write operation using file object
    // if (newfile.is_open()){   //checking whether the file is open
    //     string tp;
    //     while(getline(newfile, tp)){ //read data from file object and put it into string.
    //         cout << tp << "\n"; //print the data of the string
    //     }
    //     newfile.close(); //close the file object.
    // }
    const string& path = "/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/CMSC858D_S22_Project2_sample/ecoli.fa";
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string tp;
    getline(input_file, tp);
    cout << string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}


