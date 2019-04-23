// Computing Introduction Course
// Chapter 8
// Exercise 5

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

struct myTime
{
    int h;
    int m;
    int s;
};

myTime setTime(int h, int m, int s)
{
    myTime t;
    t.h = h % 24;
    t.m = m % 60;
    t.s = s % 60;
    return t;
}

void increase(myTime &t)
{
    t.s++;
    if (t.s == 60)
        t.m++;
    if (t.m == 60)
        t.h++;
    t.s %= 60;
    t.m %= 60;
    t.h %= 24;
}

void showTime(myTime t)
{
    if (t.h / 10 == 0)
        cout << '0' << t.h;
    else
        cout << t.h;
    cout << ":";
    if (t.m / 10 == 0)
        cout << '0' << t.m;
    else
        cout << t.m;
    cout << ":";
    if (t.s / 10 == 0)
        cout << '0' << t.s;
    else
        cout << t.s;
}

int main()
{
    /*
    example input:
        23 59 58
    output:
        +0s:    23:59:58
        +1s:    23:59:59
        +2s:    00:00:00
        +3s:    00:00:01
        +4s:    00:00:02
    */
    int h, m, s;
    cout << "Input time:";
    cin >> h >> m >> s;
    myTime t = setTime(h, m, s);
    for (int i = 0; i < 5; i++)
    {
        cout << "+" << i << "s:\t";
        showTime(t);
        cout << endl;
        increase(t);
    }

    system("pause");
    return 0;
}
