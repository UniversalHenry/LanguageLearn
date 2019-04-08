// Computing Introduction Course
// Chapter 5
// Exercise 4

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string s;
    cout << "Input a number:";
    cin >> s;
    double x = 0;
    double digit = 1;
    int sign = 0;
    if (s[0] == '-')
        sign = 1;
    for (int i = sign; i < s.length(); i++)
    {
        if (digit < 1)
        {
            x += (s[i] - '0') * digit;
            digit *= 0.1;
        }
        else if (s[i] == '.')
        {
            digit *= 0.1;
        }
        else
        {
            x = 10 * x + (s[i] - '0');
        }
    }
    x *= (1 - 2 * sign);
    cout << 2 * x << endl;
    system("pause");
    return 0;
}
