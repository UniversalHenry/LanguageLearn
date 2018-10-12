#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>

using namespace std;

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
	string input;
	char ch;
	string output;
	while(cin.get(ch)){if(isalpha(ch)||isdigit(ch))input += ch;}
	if(input.length()){
		int a=floor(sqrt(input.length()));
		int b=a+1;
		if(a*b<input.length())a=b;
		for(int i=0; i<b;i++){
			for(int j=0; j<a;j++){
				output += input[i+b*j];
			}
		}
	}else{
	cout << "Null";
	}

// time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur/CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
	int test;
	cin >> test;
    return 0;
}