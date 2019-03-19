// Computing Introduction Course 
// Chapter 3
// Exercise 4

#include <iostream>

using namespace std;

int main()
{
    double x,y;
	cin >> x;
    if(x>=10) cout << 3*x-11;
    else if(x>=1) cout << 2*x-1;
    else cout << x;
    system("pause");
	return 0;
}
