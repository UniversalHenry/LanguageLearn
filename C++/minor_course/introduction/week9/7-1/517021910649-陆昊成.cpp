// Computing Introduction Course
// Chapter 7
// Exercise 1

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

void getDate(int &dd, int &mm, int &yy)
{
    string s;
    cin >> dd;
    getchar();
    getline(cin, s, '-');
    cin >> yy;
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "JAN")
        mm = 1;
    if (s == "FEB")
        mm = 2;
    if (s == "MAR")
        mm = 3;
    if (s == "APR")
        mm = 4;
    if (s == "MAY")
        mm = 5;
    if (s == "JUN")
        mm = 6;
    if (s == "JUL")
        mm = 7;
    if (s == "AUG")
        mm = 8;
    if (s == "SEP")
        mm = 9;
    if (s == "OCT")
        mm = 10;
    if (s == "NOV")
        mm = 11;
    if (s == "DEC")
        mm = 12;
}

int main()
{
    /*
    example input:
        22-apr-19
    output:
        12
    */
    int dd, mm, yy;
    getDate(dd, mm, yy);
    cout << dd << '/' << mm << '/' << yy << endl;
    system("pause");
    return 0;
}
