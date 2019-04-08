// Computing Introduction Course
// Chapter 6
// Exercise 17

#include <iostream>
#include <cmath>

using namespace std;

int reverse(int n){
    int x = 0;
    while(abs(n) > 0){
        x = 10 * x + (n % 10);
        n /= 10;
    }
    return x;
}

int main()
{
    /*
    example input:
        12345
    output:
        54321
    */
    int n;
    cin >> n;
    cout << reverse(n) << endl;
    system("pause");
    return 0;
}
