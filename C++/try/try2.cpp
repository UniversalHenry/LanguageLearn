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

using namespace std;


int default3(int c ,const int a = 30);

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    int x = 1;
    x <<= 1;
    cout << x;
    
// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}
