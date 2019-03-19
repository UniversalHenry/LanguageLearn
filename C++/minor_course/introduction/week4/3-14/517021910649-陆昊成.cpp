// Computing Introduction Course 
// Chapter 3
// Exercise 14

#include <iostream>

using namespace std;

int main()
{   
    char c;
    int d1,h1,m1,d2,h2,m2; // assume date 1 is smaller than date 2
    cout<<"Car type(C/B/T):\n";
    cin>>c;
    cout<<"Check in time(date):\n";
    cin>>d1;
    cout<<"Check in time(hour):\n";
    cin>>h1;
    cout<<"Check in time(minutes):\n";
    cin>>m1;
    cout<<"Check in time(date):\n";
    cin>>d2;
    cout<<"Check in time(hour):\n";
    cin>>h2;
    cout<<"Check in time(minutes):\n";
    cin>>m2;
    int h = (d2-d1)*24+h2-h1+(m2-m1+59)/60;
    cout << "You should pay ";
    switch (c)
    {
        case 'C':
            if(h<=3) cout<<5*h;
            else cout<<10*h-15;
            break;
        case 'B':
            if(h<=2) cout<<10*h;
            else cout<<15*h-10;
            break;
        case 'T':
            if(h<=1) cout<<10*h;
            else cout<<15*h-5;
            break;
        default:
            break;
    }
    cout<<endl;
    system("pause");
	return 0;
}
