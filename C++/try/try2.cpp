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
    cout << default3(10);
    
// time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur / CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
    cin >> dur;
    return 0;
}

int default3(int c ,const int a){
    return c + a;
}