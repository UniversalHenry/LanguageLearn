#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
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

int main()
{
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here

    unsigned char c = 256;
    cout << int(c) << endl;
    cout << int(unsigned(c)) << endl;
    

// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}