// Computing Introduction Course 
// Chapter 2 
// Exercise 3

#include <iostream>

using namespace std;

int main()
{
    int input[9];
	for(int i = 0; i < 9; i++) cin >> input[i];
    for(int i = 0; i < 9; i++){
        cout << input[i] << '\t';
        if(i % 3 == 2) cout << endl;
    }
    system("pause");
	return 0;
}
