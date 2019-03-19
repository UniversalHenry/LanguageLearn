// Computing Introduction Course 
// Chapter 4
// Exercise 16

#include <iostream>
#include <cmath>

using namespace std;

int main()
{   
    double dx=0,x=0,s=0;
    cout<<"Input dx:";
    cin>>dx;
    while(x<1){
        s+=sqrt(1-x*x);
        x+=dx;
    }
    s*=4*dx;
    cout << "PI=" << s << endl;
    system("pause");
	return 0;
}
