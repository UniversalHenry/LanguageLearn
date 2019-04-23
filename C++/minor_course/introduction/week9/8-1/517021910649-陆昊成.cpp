// Computing Introduction Course
// Chapter 8
// Exercise 1

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

struct cplx
{
    double x = 0, y = 0;
};

cplx add(cplx c1, cplx c2)
{
    cplx c;
    c.x = c1.x + c2.x;
    c.y = c1.y + c2.y;
    return c;
}
cplx mul(cplx c1, cplx c2)
{
    cplx c;
    c.x = c1.x * c2.x - c1.y * c2.y;
    c.y = c1.y * c2.x + c1.x * c2.y;
    return c;
}
void out(cplx c)
{
    cout << c.x;
    if (c.y < 0)
        cout << c.y << "i";
    if (c.y > 0)
        cout << "+" << c.y << "i";
}
void in(cplx &c)
{
    cin >> c.x >> c.y;
}

int main()
{
    /*
    example input:
        1 2
        3 4
    output:
        Add:4+6i
        Mul:-5+10i
    */
    cplx c1, c2;
    cout << "Input complex number 1:";
    in(c1);
    cout << "Input complex number 2:";
    in(c2);
    cout << "Add:";
    out(add(c1, c2));
    cout << endl;
    cout << "Mul:";
    out(mul(c1, c2));
    cout << endl;
    system("pause");
    return 0;
}
