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
    Bin b1,b2;
    char c = 0;
    b1.str += c;
    b1.str += c;
    b1.num = 12;
    cout << b1 << endl;
    c = 255;
    b2.str += c;
    b2.num = 5;
    cout << b2 << endl;
    cout << (b2 = add_bin(b2,b1)) << endl;
    cout << (b1 = add_bin(b2,b1)) << endl;
    cout << (b2 = add_bin(b2,b1)) << endl;
    cout << b2;
    cout << "***";
    cout << read_bin(b2,4,20);

// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}

