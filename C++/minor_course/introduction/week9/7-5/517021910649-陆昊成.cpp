// Computing Introduction Course
// Chapter 7
// Exercise 5

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

bool judge(int num, int *n)
{
    bool flag = true;
    for (int i = 0; i < num / 2; i++)
    {
        if (n[i] != n[num - i - 1])
        {
            flag = false;
            break;
        }
    }
    return flag;
}

int main()
{
    /*
    example input:
        7
        10 5 30 67 30 5 10
    output:
        True
    example input:
        7
        10 5 30 67 5 5 10
    output:
        False
    */
    int n[1000];
    int num;
    cout << "Input number:";
    cin >> num;
    cout << "Input data:";
    for (int i = 0; i < num; i++)
    {
        cin >> n[i];
    }
    if (judge(num, n))
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
    system("pause");
    return 0;
}
