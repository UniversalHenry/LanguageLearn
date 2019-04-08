// Computing Introduction Course
// Chapter 6
// Exercise 23

#include <iostream>
#include <cmath>

using namespace std;

double a = 0;
int m;

int area(double r, int n)
{
    if (n == 0)
        return 0;
    a += sqrt(r * r - (n * r / m) * (n * r / m)) / 2 * (r / m);
    n--;
    a += sqrt(r * r - (n * r / m) * (n * r / m)) / 2 * (r / m);
    area(r, n);
}

int main()
{
    /*
    example input:
        10000
        1
    output:
        3.14159
    */
    double r;
    cout << "n:";
    cin >> m;
    cout << "r:";
    cin >> r;
    area(r, m);
    cout << 4 * a << endl;
    system("pause");
    return 0;
}
