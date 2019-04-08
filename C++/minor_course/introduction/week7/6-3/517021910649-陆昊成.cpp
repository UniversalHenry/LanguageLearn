// Computing Introduction Course
// Chapter 6
// Exercise 3

#include <iostream>
#include <cstring>

using namespace std;

void stringCopy(string s1, string &s2)
{
    s2 = s1;
}

int main()
{
    /*
    example input:
        123
    output:
        123
    */
    string s1, s2;
    cin >> s1;
    stringCopy(s1, s2);
    cout << s2 << endl;
    system("pause");
    return 0;
}
