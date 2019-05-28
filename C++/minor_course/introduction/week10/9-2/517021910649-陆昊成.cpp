// Computing Introduction Course
// Chapter 9
// Exercise 2

#include <iostream>
#include "seq.h"

using namespace std;

int main()
{
    /*
    output:
        label 0
        label 1
        label 2
        label 3
        label 4
        label 5
        label 6
        label 7
        label 8
        label 9

        test 5
        test 6
        test 7
        test 8
        test 9
        test 10
        test 11
        test 12
        test 13
        test 14
    */
    for (int i = 0; i < 10; i++)
        cout << GetNextLabel() << endl;
    cout << endl;
    setLabel("test ");
    setInitNumber(5);
    for (int i = 0; i < 10; i++)
        cout << GetNextLabel() << endl;
    system("pause");
    return 0;
}
