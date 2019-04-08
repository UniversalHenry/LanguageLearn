// Computing Introduction Course
// Chapter 6
// Exercise 6

#include <iostream>
#include <cstring>

using namespace std;

int searcher(int *a, int size, int high, int low, int target)
{
    if (a[(high + low) / 2] == target)
        return (high + low) / 2; // return target place
    if (high == low)
        return -1; // -1 indicates not found
    if (a[(high + low) / 2] > target)
        return searcher(a, size, (high + low) / 2, low, target);
    else
        return searcher(a, size, high, (high + low) / 2, target);
}

int main()
{
    /*
    example input:
        9
        1 2 3 4 5 6 7 8 9
        8
    output:
        7
    */
    int n;
    cout << "Input search size:";
    cin >> n;
    int a[n];
    cout << "Input the array(ascending order):";
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Input the target:";
    int target;
    cin >> target;
    cout << "The target place is(-1 indicates not found):";
    cout << searcher(a, n, n - 1, 0, target) << endl;
    system("pause");
    return 0;
}
