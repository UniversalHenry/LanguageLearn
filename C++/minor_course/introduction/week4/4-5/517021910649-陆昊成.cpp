// Computing Introduction Course 
// Chapter 4
// Exercise 5

#include <iostream>

using namespace std;

int main()
{   
    int a=0,b=1;
    for(int i=0;i<15;i++){
        cout << "F" << i << ":\t"<< a << endl;
        int c=a;
        a=b;
        b=c+b;
    }
    system("pause");
	return 0;
}
