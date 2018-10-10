#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <set>
#include <ctime>

using namespace std;

int main(void){

    double dur;
    clock_t start,end;
    start = clock();
    
    long order_num = 0;

    char* order_file_name[]={"data/order.0.0","data/order.0.3","data/order.1.1","data/order.2.2"};
    int order_file_num = 4;
    string input;
    for(int i = 0;i < order_file_num;i++){
        ifstream order_file(order_file_name[i]);
        while(getline(order_file,input)){
            order_num++;
        }
        order_file.close();
    }

    end = clock();
    dur = (double)(end - start);
    
    cout << "\nOrder Number:" << order_num << "\t";
    printf("\nUseTime:%f\n",(dur/CLOCKS_PER_SEC));

	cout << "\nProgram finished.";
	int test;
	cin >> test;
    return 0;
}