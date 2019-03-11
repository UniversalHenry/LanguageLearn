// Computing Introduction Course 
// Chapter 2 
// Exercise 4

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double t,s;
    cin >> t >> s;
    cout << "Nominal wages:\t" << fixed << setprecision(2) << s*t << "\tyuan" << endl;
    cout << "Real wages:\t" << s*t*0.9 << "\tyuan" << endl;
    system("pause");
	return 0;
}
