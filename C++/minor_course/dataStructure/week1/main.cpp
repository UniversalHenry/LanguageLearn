# include <iostream>

using namespace std;

int factorial(int x){
	if (x<= 0) return 1;
	return x*factorial(x-1);
}

int main(){
	int k;
	cout << "Please input k:";
	cin >> k;
	cout << factorial(k);
	cin >> k;
	return 0;
}