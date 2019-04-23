// Computing Introduction Course
// Chapter 7
// Exercise 8

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

double *calculate(int num, double *n)
{
    double *res = new double[2];
    res[0] = 0;
    for (int i = 0; i < num; i++)
    {
        res[0] += n[i];
    }
    res[0] /= num;
    res[1] = 0;
    for (int i = 0; i < num; i++)
    {
        res[1] += (n[i] - res[0]) * (n[i] - res[0]);
    }
    res[1] /= num;
    return res;
}

int main()
{
    /*
    example input:
        7
        10 5 30 67 30 5 10
    output:
        means:22.4286   var:431.102
    */
    double n[1000];
    int num;
    cout << "Input number:";
    cin >> num;
    cout << "Input data:";
    for (int i = 0; i < num; i++)
    {
        cin >> n[i];
    }
    double *result = calculate(num, n);
    cout << "means:" << result[0] << "\tvar:" << result[1] << endl;
    system("pause");
    return 0;
}
