// Computing Introduction Course
// Chapter 8
// Exercise 3

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

int GCF(int n, int m)
{
    if (n == 0)
        return 0;
    n = abs(n);
    m = abs(m);
    while (m != n)
    {
        if (m > n)
        {
            int x = m;
            m = n;
            n = x;
        }
        if (n % m == 0)
        {
            n = m;
        }
        else
        {
            n = n % m;
        }
    }
    return n;
}

struct rationalT
{
    int num, den;
};

rationalT CreateRational(int num, int den)
{
    rationalT r;
    r.num = num;
    r.den = den;
    if (r.den == 0)
    {
        r.den = 1;
        cout << "input error" << endl;
    }
    int gcf = GCF(r.num, r.den);
    if (gcf == 0)
        r.den = 1;
    else
    {
        r.num /= gcf;
        r.den /= gcf;
    }
    if (r.den < 0)
    {
        r.den *= -1;
        r.num *= -1;
    }
    return r;
}

rationalT AddRational(rationalT r1, rationalT r2)
{
    rationalT r;
    r.num = r1.num * r2.den + r1.den * r2.num;
    r.den = r1.den * r2.den;
    int gcf = GCF(r.num, r.den);
    if (gcf == 0)
        r.den = 1;
    else
    {
        r.num /= gcf;
        r.den /= gcf;
    }
    if (r.den < 0)
    {
        r.den *= -1;
        r.num *= -1;
    }
    return r;
}

rationalT MultiplyRational(rationalT r1, rationalT r2)
{
    rationalT r;
    r.num = r1.num * r2.num;
    r.den = r1.den * r2.den;
    int gcf = GCF(r.num, r.den);
    if (gcf == 0)
        r.den = 1;
    else
    {
        r.num /= gcf;
        r.den /= gcf;
    }
    if (r.den < 0)
    {
        r.den *= -1;
        r.num *= -1;
    }
    return r;
}

void GetRational(rationalT r)
{
    cout << double(r.num) / r.den;
}

void PrintRational(rationalT r)
{
    cout << r.num << '/' << r.den;
}

int main()
{
    /*
    example input:
        2 6
        1 6
    output:
        r1:1/3
        r1:0.333333
        r2:1/6
        r2:0.166667
        r1+r2:1/2
        r1+r2:0.5
        r1*r2:1/18
        r1*r2:0.0555556
    */
    rationalT r1, r2;
    int n, d;
    cout << "Input rational number 1:";
    cin >> n >> d;
    r1 = CreateRational(n, d);
    cout << "Input rational number 2:";
    cin >> n >> d;
    r2 = CreateRational(n, d);

    cout << "r1:";
    PrintRational(r1);
    cout << "\nr1:";
    GetRational(r1);
    cout << endl;

    cout << "r2:";
    PrintRational(r2);
    cout << "\nr2:";
    GetRational(r2);
    cout << endl;

    cout << "r1+r2:";
    PrintRational(AddRational(r1, r2));
    cout << "\nr1+r2:";
    GetRational(AddRational(r1, r2));
    cout << endl;

    cout << "r1*r2:";
    PrintRational(MultiplyRational(r1, r2));
    cout << "\nr1*r2:";
    GetRational(MultiplyRational(r1, r2));
    cout << endl;

    system("pause");
    return 0;
}
