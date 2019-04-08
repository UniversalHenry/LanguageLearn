// Computing Introduction Course
// Chapter 6
// Exercise 20

#include <iostream>

using namespace std;

int count()
{
    static int a = 0;
    return ++a;
}

int main()
{
    /*
    example input:
        10
    output:
        1       2       3       4       5       6       7       8       9       10
    */
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cout << count() << '\t';
    cout << endl;
    system("pause");
    return 0;
}
