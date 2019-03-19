// Computing Introduction Course 
// Chapter 3
// Exercise 8

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double minus,salary;
    int method;
	cout << "Input salary method(1/2/3):" << endl;
    bool flag = true;
    while(flag){
        cin >> method;
        switch (method)
        {
            double h,m;
            case 1:
                cout << "Working hours:" << endl;
                cin >> h;
                cout << "Salary per hour:" << endl;
                cin >> m;
                salary = h*m;
                flag=false;
                break;
            case 2:
                cout << "Processed goods:" << endl;
                cin >> h;
                cout << "Salary per goods:" << endl;
                cin >> m;
                salary = h*m;
                flag=false;
                break;
            case 3:
                cout << "Fixed salary:" << endl;
                cin >> salary;
                flag=false;
                break;
            default:
                break;
        }
    }
    minus=0;
    if(salary>=2000)minus+=((salary>2500?2500:salary)-2000)*0.05;
    if(salary>=2500)minus+=((salary>4000?2500:salary)-2500)*0.1;
    if(salary>=4000)minus+=(salary-4000)*0.15;
    cout << "Nominal wages:\t" << salary << endl;
    cout << "Real wages:\t" << salary - minus<< endl;
    system("pause");
	return 0;
}
