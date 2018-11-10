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
    int x = 0;
    bool t = true;
    bool f = false;
    cout << x+f << "\t" << x+t << "\t" << x+t+t+t+t << endl;
    
// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}
