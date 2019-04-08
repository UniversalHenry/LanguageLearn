// Computing Introduction Course
// Chapter 5
// Exercise 3

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string s;
    cout << "Input a string:";
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] <= 'z' && s[i] >= 'a')
            cout << int(s[i] - 'a' + 1) << ' ';
        else if (s[i] <= 'Z' && s[i] >= 'A')
            cout << int(s[i] - 'A' + 1) << ' ';
        else
            cout << "0 ";
    }
    cout << endl;
    system("pause");
    return 0;
}
