// Computing Introduction Course 
// Chapter 4
// Exercise 4

#include <iostream>

using namespace std;

int main()
{   
    int x0;
    cin >> x0;
    int x = 1;
    while(x0/x>0){
        x *= 10;
    }
    while(x>1){
        x /= 10;
        cout << x0/x << " ";
        x0 = x0 % x;
    }
    system("pause");
	return 0;
}
