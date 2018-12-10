#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <ctime>
#include <cstring>
#include "huffman.h"

using namespace std;

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    {
        string inputFilename, outputFilename;
        inputFilename = "try.txt";
        outputFilename = "output.txt";
        ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
        ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
        Huffman hfm_coder;
        char c;
        string input;
        vector<char> output;
        while (ifs.get(c)) input += c;
        output = hfm_coder.encode(input);
        for(int i = 0; i < output.size(); i++) ofs.put(output[i]);
        ofs.close();
        ifs.close();
    }
    {
        string inputFilename, outputFilename;
        inputFilename = "output.txt";
        outputFilename = "returned.txt";
        ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
        ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
        Huffman hfm_coder;
        char c;
        string input, output;
        while (ifs.get(c)) input += c;
        output = hfm_coder.decode(input);
        for(int i = 0; i < output.size(); i++) ofs.put(output[i]);
        ofs.close();
        ifs.close();
    }

    // Bin b1,b2;
    // string s;
    // char c1 = 255,c2 = 0;
    // s += c1;
    // b1 = gen_bin(s,2);
    // s[0] = c2;
    // b2 = gen_bin(s,1);
    // cout << (b1 = add_bin(b1,b2)) << endl;
    // cout << (b1 = add_bin(b1,b2)) << endl;
    // cout << (b1 = add_bin(b1,b2)) << endl;
    // cout << (b1 = add_bin(b1,b2)) << endl;
    // cout << (b1 = add_bin(b1,b2)) << endl;
    // cout << (b1 = add_bin(b1,b2)) << endl;
    // cout << (b2 = add_bin(b1,b2)) << endl;
    // cout << (b2 = add_bin(b1,b2)) << endl;
    // cout << (b2 = add_bin(b1,b2)) << endl;
    // cout << (b2 = add_bin(b1,b2)) << endl;
    // cout << (b2 = add_bin(b1,b2)) << endl;

// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}

