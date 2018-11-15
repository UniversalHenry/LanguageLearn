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
#include <iomanip>

using namespace std;

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    ofstream fout("Gprogram");
    const double pi = 3.1415926535898;
    double theta = 0;
    double r = 0;
    double h = 0;
    int n = 30;
    double dtheta = pi/360;
    double dr = (8 / (2*pi)) * dtheta;
    double dh = -2.5 / 36 * dr; 
    while(true){
        double x = 40 + r * cos(theta);
        double y = 50 + r * sin(theta);
        fout << "N" << n ;
        fout << "X" << setprecision(5) << x;
        fout << "Y" << setprecision(5) << y;
        fout << "Z" << setprecision(3) << h;
        fout << "F100" << endl;
        r += dr;
        h += dh;
        theta += dtheta;
        n++;
        if(theta > 9*pi) break;
    }
    theta = pi;
    r = 0;
    h = -2.5;
    dtheta = pi/360;
    dr = (8 / (2*pi)) * dtheta;
    dh = 2.5 / 36 * dr; 
    while(true){
        double x = 40 + r * cos(theta);
        double y = 50 + r * sin(theta);
        fout << "N" << n ;
        fout << "X" << setprecision(5) << x;
        fout << "Y" << setprecision(5) << y;
        fout << "Z" << setprecision(3) << h;
        fout << "F100" << endl;
        r += dr;
        h += dh;
        theta += dtheta;
        n++;
        if(theta > 10*pi) break;
    }
    
    
    system("pause");
    return 0;
}
