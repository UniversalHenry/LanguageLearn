#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>

using namespace std;

int main(void){
// time start
/*    double dur;
    clock_t start,end;
    start = clock();
*/
// main function
	string input;
	char ch;
	string output;
	while(cin.get(ch)){if(ch=='\n')break;if(isalpha(ch)||isdigit(ch))input += ch;}
	if(input.length()){
//		cout << input << endl;
		int b=ceil(sqrt(input.length()));
		int a=b-1;
		if(a*b<input.length())a=b;
//		cout << a << '\t' << b;
		for(int i=0; i<b;i++){
			for(int j=0; j<a;j++){
				cout << input[i+b*j];
			}
			cout << ' ';
		}
	}else{
		cout << "Null";
	}

// time stop
/*    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur/CLOCKS_PER_SEC));
*/
	cout << "\nProgram finished.";
	int test;
	cin >> test;
    return 0;
}