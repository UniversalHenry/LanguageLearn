// Computing Introduction Course
// Chapter 7
// Exercise 3

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

char *itos(int n)
{
    int sign = 1;
    char chn[100];
    int num = 0;
    if (n < 0)
    {
        sign = -1;
        n *= -1;
    }
    if (n == 0)
        sign = 0;
    while (n > 0)
    {
        chn[num] = ('0' + n % 10);
        n /= 10;
        num++;
    }
    char *c;
    if (sign == 0)
    {
        c = new char[2];
        c[0] = '0';
        c[1] = '\0';
    }
    if (sign == -1)
    {
        c = new char[num + 2];
        c[0] = '-';
        for (int i = 1; i < num + 1; i++)
        {
            c[i] = chn[num - i];
        }
        c[num + 1] = '\0';
    }
    if (sign == 1)
    {
        c = new char[num + 1];
        for (int i = 0; i < num; i++)
        {
            c[i] = chn[num - 1 - i];
        }
        c[num] = '\0';
    }
    return c;
}

int main()
{
    /*
    example input:
        -123456
    output:
        -123456
    */
    int n;
    cin >> n;
    cout << itos(n) << endl;
    system("pause");
    return 0;
}
