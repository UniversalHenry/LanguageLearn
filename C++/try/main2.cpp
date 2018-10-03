#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <stack>
#include <iterator>
#include <cmath>
#include <sstream>
using namespace std;
int main()
{   
    string s = "-21.3456abs";
    stringstream ss;
    double x;
    ss << s;
    ss >> x;
    cout << x << endl;

    cout << "Program finished.";
    int test;
    cin >> test;
    return 0;
}
